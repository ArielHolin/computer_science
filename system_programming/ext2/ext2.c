#include <stdio.h> 		/* printf */
#include <sys/stat.h> 	/* open */
#include <unistd.h> 	/* open */
#include <fcntl.h> 		/* O_RDONLY */
#include <string.h>     /*  memcpy  */
#include <stdlib.h>     /*  malloc, free  */

#include "ext2.h"

#define BASE_OFFSET 1024  
#define BLOCK_OFFSET(block) (BASE_OFFSET + (block-1)*block_size)

static unsigned int block_size = 1024;  

static void read_inode(int fd, int inode_no, 
            const struct ext2_group_desc *group,struct ext2_inode *inode);

static void read_dir(int, const struct ext2_inode*);
static int get_inode_number(int, const struct ext2_inode*, const char*);

int main(size_t argc, char *argv[])
{
    int fd = 0;
    int i = 0;
    struct ext2_super_block super_block;
    struct ext2_inode inode;
    struct ext2_group_desc group;
    // struct EXT2_N_BLOCKS
    char *mount_folder = "/dev/ram0";
    char *file_name = NULL;

    /* make sure we have enough arguments */
    if (1 >= argc)
    {
    	printf("Not enought parameters\n");
    	return 0;
    }
    file_name = argv[1];
    
    printf("Seeking %s\n",file_name);

    fd = open(mount_folder, O_RDONLY);

    /* Reads the boot section and the superblock */
    lseek(fd, BASE_OFFSET, SEEK_SET);  //skip boot, 1024 bytes
    read(fd, &super_block, sizeof(super_block));    //read superblock
 
    // maybe there is an error ??
    if (super_block.s_magic != EXT2_SUPER_MAGIC)
    {
        printf("Error reading super block\n");
        return 1; //bad file system
    } 

	/* read group descriptor */
	lseek(fd, BASE_OFFSET + block_size, SEEK_SET);
	read(fd, &group, sizeof(group));

    /*  search for file inode number    */
    read_inode(fd, 2, &group, &inode); 
	int inode_number = get_inode_number(fd, &inode, file_name);
    if (-1 == inode_number)
    {
        printf("Error, file not found\n");
        return 0;
    }

    // read the found inode
    read_inode(fd, inode_number, &group, &inode); 
    int buff_size =  inode.i_size;
    
    printf("test, inode num = %d, buff_size = %u: \n",inode_number, buff_size);
    char buffer[buff_size + 1];
    lseek(fd, BLOCK_OFFSET(inode.i_block[0]), SEEK_SET);
    read(fd, buffer, buff_size);
    buffer[buff_size] = 0;
    printf("Buffer:\n%s",buffer);
    printf("test end\n");

    printf("All done, closing fd\n");
    close(fd);

    return 0;
}

static void read_inode(int fd, int inode_no, 
            const struct ext2_group_desc *group,struct ext2_inode *inode)
{
	lseek(fd, BLOCK_OFFSET(group->bg_inode_table)+(inode_no-1)*sizeof(struct ext2_inode), SEEK_SET);
	read(fd, inode, sizeof(struct ext2_inode));
} /* read_inode() */

static int get_inode_number(int fd, const struct ext2_inode *inode, const char *f_name)
{
    char block[1024];

	if (S_ISDIR(inode->i_mode)) 
    {
		struct ext2_dir_entry_2 *entry;
		unsigned int size = 0;

		lseek(fd, BLOCK_OFFSET(inode->i_block[0]), SEEK_SET);
		read(fd, block, block_size);                /* read block from disk*/

		entry = (struct ext2_dir_entry_2 *) block;
		while((size < inode->i_size) && entry->inode) 
        {
			if (0 == strncmp(entry->name, f_name,entry->name_len))
            {
                return (entry->inode);
            }

			entry = (void*) entry + entry->rec_len;
			size += entry->rec_len;
		}
	}

    return -1;
}

static void read_dir(int fd, const struct ext2_inode *inode)
{
	char block[1024];

	if (S_ISDIR(inode->i_mode)) 
    {
		struct ext2_dir_entry_2 *entry;
		unsigned int size = 0;

		lseek(fd, BLOCK_OFFSET(inode->i_block[0]), SEEK_SET);
		read(fd, block, block_size);                /* read block from disk*/

		entry = (struct ext2_dir_entry_2 *) block;  /* first entry in the directory */
                /* Notice that the list may be terminated with a NULL
                   entry (entry->inode == NULL)*/
		while((size < inode->i_size) && entry->inode) 
        {
			char file_name[EXT2_NAME_LEN+1];
			memcpy(file_name, entry->name, entry->name_len);
			file_name[entry->name_len] = 0;     /* append null character to the file name */
			printf("%10u %s", entry->inode, file_name);
			printf("\t\t,len = %u\n", entry->rec_len);
			entry = (void*) entry + entry->rec_len;
			size += entry->rec_len;
		}
	}
} /* read_dir() */
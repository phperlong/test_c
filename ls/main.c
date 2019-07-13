#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_PATH 1024
#define HANG_LENGTH 4096
#define NAME_LENGTH 20

int set_mode = 0;
int set_num = 0;

void mode_to_letter(int mode,char *str)
{
    /*-------这个函数用来把模式值转化为字符串------*/
    str[0]='-'; /*------这里的S_*****都是宏定义，用来判断模式属性-*/
    if(S_ISDIR(mode)) str[0]='d';/*-文件夹-*/
    if(S_ISCHR(mode)) str[0]='c';/*-字符设备-*/
    if(S_ISBLK(mode)) str[0]='b';/*-块设备-*/
    if(mode & S_IRUSR) str[1]='r';/*--用户的三个属性-*/
    else str[1]='-';
    if(mode & S_IWUSR) str[2]='w';
    else str[2]='-';
    if(mode & S_IXUSR) str[3]='x';
    else str[3]='-';
    if(mode & S_IRGRP) str[4]='r';/*--组的三个属性-*/
    else str[4]='-';
    if(mode & S_IWGRP) str[5]='w';
    else str[5]='-';
    if(mode & S_IXGRP) str[6]='x';
    else str[6]='-';
    if(mode & S_IROTH) str[7]='r';/*-其他人的三个属性-*/
    else str[7]='-';
    if(mode & S_IWOTH) str[8]='w';
    else str[8]='-';
    if(mode & S_IXOTH) str[9]='x';
    else str[9]='-';
    str[10]='\0';
}

void split(char *p,char *str,char tmp[32][NAME_LENGTH]){
	/*
		传入一个数组进行p和一个以什么进行分割的str，返回切片后的值
	*/
	int i = 0, j = 0;
    char *p1 = (char *)malloc(1024);
    while((p1 = (char *)strchr(p, *str)) != NULL) //必须使用(char *)进行强制类型转换
    {
        strncpy(tmp[i], p, strlen(p) - strlen(p1));
        p = p1 + 1;
        i++;
    }
    strncpy(tmp[i], p, strlen(p));
}

void dirwalk(char *dir,void(*fcn)(int,char *))
{
    char name[MAX_PATH];
    struct dirent *dp;
    DIR *dfd;
    set_num++;
    if ((dfd = opendir(dir)) == NULL)
    {
        fprintf(stderr,"dirwalk: can't open %s \n",dir);
        return;
    }
    while ((dp = readdir(dfd)) != NULL)
    {
        if (strcmp(dp->d_name,".") == 0 || strcmp(dp->d_name,"..") == 0)
        {
            continue;
        }
        if (strlen(dir) + strlen(dp->d_name)+2 > sizeof(name))
        {
            fprintf(stderr, "dirwalk: name %s %s tolong\n", dir,dp->d_name);
        }
        else
        {
            sprintf(name, "%s/%s", dir, dp->d_name);
            (*fcn)(set_mode,name);
        }
    }
    closedir(dfd);
}

char *changeTime(time_t time)
{
    struct tm *lt;
    lt = localtime(&time);
    char *nowtime = (char *)malloc(sizeof(char)* 24);
    memset(nowtime,0,sizeof(nowtime));
    strftime(nowtime,24,"%Y-%m-%d %H:%M:%S",lt);
    return nowtime;
}

char *find_user(int uid)
{
        int fd,flag,num;
        char buf[HANG_LENGTH];
        char name[NAME_LENGTH];
        char *ptr = NULL;

        char cmp_str[HANG_LENGTH];
        char tmp[32][NAME_LENGTH] = {0};
        sprintf(cmp_str,"%d",uid);
        fd = open("/etc/passwd",O_RDONLY);
        while((flag = read(fd,buf,sizeof(buf)))>0)
        {
           ptr = strtok(buf,"\n");
           while (ptr != NULL)
           {
                //printf("%s \n",ptr);
                split(ptr,":",tmp);
                if(strcmp(tmp[2],cmp_str) == 0)
                {
                    char *ptr_2 = tmp[0];
                    return ptr_2;
                }
                memset(tmp,0,sizeof(tmp));
                ptr = strtok(NULL,"\n");
           }
        }
}

char *find_group(int gid)
{
        int fd,flag,num;
        char buf[HANG_LENGTH];
        char name[NAME_LENGTH];
        char *ptr = NULL;
        char cmp_str[HANG_LENGTH];
        char tmp[32][NAME_LENGTH] = {0};
        sprintf(cmp_str,"%d",gid);
        fd = open("/etc/group",O_RDONLY);
        while((flag = read(fd,buf,sizeof(buf)))>0)
        {
           ptr = strtok(buf,"\n");
           while (ptr != NULL)
           {
                //printf("%s \n",ptr);
                split(ptr,":",tmp);
                if(strcmp(tmp[2],cmp_str) == 0)
                {
                    char *ptr_2 = tmp[0];
                    return ptr_2;
                }
                memset(tmp,0,sizeof(tmp));
                ptr = strtok(NULL,"\n");
           }
        }
 }

void fsize(int set_mode,char *name)
{
	struct stat stbuf;
//    printf("%s \n",name);
	if (stat(name,&stbuf) == -1)
	{
		//fprintf(stderr, "fsize: can't access %s \n", name);
		return;
	}
	if ((stbuf.st_mode & S_IFMT) == S_IFDIR && set_num == 0)
	{
        dirwalk(name,fsize);
	}
	if(set_mode == 1)
	{
        char *user = NULL;
        char *group = NULL;
        char mode[10] = {0};
	    char *p_time = changeTime(stbuf.st_mtime);
	    //printf("%d:%d  ",stbuf.st_uid,stbuf.st_gid);
        user = find_user(stbuf.st_uid);
        group = find_group(stbuf.st_gid);
        mode_to_letter(stbuf.st_mode,mode);
    	printf("%s  %8ld %s:%s %s %s\n",mode,stbuf.st_size,user,group,p_time,name);
    	free(p_time);
	}else if(set_mode == 0)
	{
        printf("%s  ",name);
	}

}

void main(int argc,char **argv)
{
    char *name;
	if (argc == 1)
		fsize(set_mode,".");
	else if(argc == 2)
	{
	    if((*++argv)[0] == '-')
	    {
            if((*argv)[1] == 'l')
            {
                set_mode = 1;
                name = ".";
            }else{
                printf("fatol:ls -l or ls path\n");
                exit(0);
            }
	    }else
	    {
            set_mode = 0;
            name = *argv;
	    }
	}else if(argc == 3)
	{
	    if((*++argv)[0] == '-')
	    {
            if((*argv)[1] == 'l')//方便扩展
            {
                set_mode = 1;
                name = *++argv;
            }
	    }else{
	        printf("fatol:ls -l path\n");
	        exit(0);
	    }
	}else
	{
	    printf("fatol:ls -l path or ls -l or ls path");
	    exit(0);
	}
    fsize(set_mode,name);
}
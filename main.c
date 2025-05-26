#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <getopt.h>
#include <dirent.h>
#include "functii1.h"
#include "functii2.h"
#include "functii3.h"
#include "functii4.h"
#include <errno.h>

//pentru task 1
void sort_arg(int argc, char *argv[], ARG **argument, ARG **option, ARG **flag) {
    for (int i = 0; i < argc; i++) {
        if(is_short(argv[i])) 
        {
            if(atoi(argv[i]) || (i + 1 < argc && atoi(argv[i + 1]))) 
            {
                opt(argv[i], argv[i + 1], option);
                if(strlen((*option)->data.id) > 2) 
                {
			        char *dup = strdup((*option)->data.id);
			        (*option)->data.id = dup;
                    farg((*option)->data.id, option);
                    (*option)->data.id[2] = '\0';
                }

                if(atoi(argv[i + 1])) i++;
            }
            else 
            {
                pushflag(flag, argv[i]);
                if(strlen((*flag)->data.id) > 2) 
                {
			        char *dup = strdup((*flag)->data.id);
			        (*flag)->data.id = dup;
                     farg((*flag)->data.id, flag);
                    (*flag)->data.id[2] = '\0';
                }
            }
        }
        else add_arg(argument, argv[i]);
    }

}

//pentru task 2
void util_ls(char* path, FILE *output, nod **stack, int r, int d, int hr) 
{   //hr = human readable
    // d - director
    //r = recursiv

    nod *temp = NULL;
    int fl = 0;

    //fprintf(output, "%d %d %d\n", r, d, hr);

    //push(stack, path);
    push(&temp, path);

    while(temp != NULL) {

        Data2 current_data = pop(&temp);
        char *current_path = current_data.name;
        DIR *dir = opendir(current_path);



        if (dir == NULL)//ERORCHECK
        {
            fprintf(stderr, "Error opening directory %s (util_ls function)\n", path);
            free(current_path);
            exit(EXIT_FAILURE);
        }

        struct dirent *entry;

        while((entry = readdir(dir))) 
        {
                if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                    if(fl == 0) {
                         struct stat dirStat;
                        if (stat(".", &dirStat) == 0) {
                           if(hr)
                                fprintf(output ,"%.1fK %s\n", dirStat.st_size / 1024.0, ".");
                           else
                                fprintf(output, "%ld %s\n", dirStat.st_size, ".");
                            if(stat("..", &dirStat) == 0) {
                                if(hr)
                                    fprintf(output ,"%.1fK %s\n", dirStat.st_size / 1024.0, "..");
                                else
                                    fprintf(output, "%ld %s\n", dirStat.st_size, "..");
                            }
                        }
                    }


                    fl++;
                    
                }


                char fullpath[PATH_MAX];
                snprintf(fullpath, PATH_MAX, "%s/%s", current_path, entry->d_name);

                struct stat fileStat;
                if(lstat(fullpath, &fileStat) == 0) 
                {

                    if (S_ISLNK(fileStat.st_mode))//skip simbolic lynk pt a evita link-loop
                        continue;

                    if(S_ISREG(fileStat.st_mode) && !d)///doar text nu si directoare
                        {
                            nod* aux = findir(*stack, current_path);
                            if(aux) {
                                //fprintf(output, "%s\n", current_path);
                                addbegin(&aux->content, entry->d_name, fileStat.st_size);
                            }

                        }else
                            if(S_ISDIR(fileStat.st_mode))
                            {
                                push(stack, fullpath);
                                push(&temp, fullpath);
                            }
                }
            }
        closedir(dir);
        free(current_path);
        if(!d && !r)
            break;
    }

    sortdirs(stack);
    sortfiles(&(*stack)->content);

    printStack(*stack, output, hr);
    //printlist((*stack)->content, output, hr);

    freestack(temp);
}


//pt task 3
char* lcdir(const char* dir1, const char* dir2) {
     char *dir1_cpy = strdup(dir1);
    char *dir2_cpy = strdup(dir2);
    if (!dir1_cpy || !dir2_cpy) {
        free(dir1_cpy);
        free(dir2_cpy);
        return NULL;
    }

    char **s1 = NULL, **s2 = NULL;
    int c1 = 0, c2 = 0;
    char *tok, *save;

    tok = strtok_r(dir1_cpy, "/", &save);
    while (tok) {
        char **temp = realloc(s1, (c1 + 1) * sizeof *s1);
        if (!temp) {
            free(dir1_cpy); free(dir2_cpy);
            return NULL;
        }
        s1 = temp;
        s1[c1++] = strdup(tok);
        tok = strtok_r(NULL, "/", &save);
    }

    tok = strtok_r(dir2_cpy, "/", &save);
    while (tok) {
        char **temp = realloc(s2, (c2 + 1) * sizeof *s2);
        if (!temp) {
            for (int i = 0; i < c1; i++) free(s1[i]);
            free(s1);
            free(dir1_cpy); free(dir2_cpy);
            return NULL;
        }
        s2 = temp;
        s2[c2++] = strdup(tok);
        tok = strtok_r(NULL, "/", &save);
    }

    int limit = c1 < c2 ? c1 : c2;
    int last = -1;
    for (int i = 0; i < limit; i++) {
        if (strcmp(s1[i], s2[i]) != 0)
            break;
        last = i;
    }

    if (last < 0) {
        for (int i = 0; i < c1; i++) free(s1[i]);
        for (int i = 0; i < c2; i++) free(s2[i]);
        free(s1); free(s2);
        free(dir1_cpy); free(dir2_cpy);
        return NULL;
    }

    size_t len = 1;
    for (int i = 0; i <= last; i++)
        len += strlen(s1[i]) + 1;
    char *common = malloc(len + 1);
    if (!common) {
        for (int i = 0; i < c1; i++) free(s1[i]);
        for (int i = 0; i < c2; i++) free(s2[i]);
        free(s1); free(s2);
        free(dir1_cpy); free(dir2_cpy);
        return NULL;
    }
    common[0] = '\0';
    for (int i = 0; i <= last; i++) {
        strcat(common, "/");
        strcat(common, s1[i]);
    }

    for (int i = 0; i < c1; i++) free(s1[i]);
    for (int i = 0; i < c2; i++) free(s2[i]);
    free(s1); free(s2);
    free(dir1_cpy); free(dir2_cpy);
    return common;
}


void dir_tree(nod *nodes) {
    if (!nodes || !nodes->dir_name)
        return;

    DIR *dir = opendir(nodes->dir_name);
    if (!dir) //ERORCHECK
    {
        fprintf(stderr, "Error opening directory %s: %s\n",
                nodes->dir_name, strerror(errno));
        exit(EXIT_FAILURE);
    }

    struct dirent *entry;
    while ((entry = readdir(dir))) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        char fullpath[PATH_MAX];
        snprintf(fullpath, sizeof(fullpath), "%s/%s",
                 nodes->dir_name, entry->d_name);

        struct stat fileStat;
        if (lstat(fullpath, &fileStat) < 0) //ERORCHECK
        {
            fprintf(stderr, "lstat failed for %s: %s\n", fullpath, strerror(errno));
            continue;
        }
        if (S_ISLNK(fileStat.st_mode))
            continue;
        if (S_ISDIR(fileStat.st_mode))
            adoptchild(nodes, fullpath);
    }
    closedir(dir);
    for (int i = 0; i < nodes->child_no; i++)
        dir_tree(nodes->next);
}

int main(int argc, char **argv){
    if (strcmp(argv[1], "task1") == 0)//////////////// 
    {
        FILE *input, *output;
        ARG *argument, *option, *flag;
	    argument = NULL;
	    option = NULL;
	    flag = NULL;
        sort_arg(argc - 2, argv + 2, &argument, &option, &flag);

        char infile[256] = {0}, outfile[256] = {0};
        if (strncmp(argv[argc - 2], "--file=", 7) == 0) 
        {
	    	const char* posin = strstr(argv[argc - 2] + 7, "teste");
	        if(posin)
	        	strcpy(infile, posin);
	        else
                strcpy(infile, argv[argc - 2] + 7);
        }
	    if (strncmp(argv[argc - 1], "--out=", 6) == 0) 
        {
	    	const char* posout = strstr(argv[argc - 1] + 6, "ref");
	        if(posout)
	        	strcpy(outfile, posout);
	        else
                strcpy(outfile, argv[argc - 1] + 6);
        }

        input = fopen(infile, "r");
        if (!input) //ERORCHECK
        {
            fprintf(stderr, "Error opening file for reading: %s", infile);
            exit(1);
        }

        output = fopen(outfile, "w");
        if (!output) //ERORCHECK
        {
            perror("Error opening file for writing");
            fclose(input);
            exit(2);
        }

        char line[100];

        while (fgets(line, sizeof(line), input)) ////////////afisare task1
        {

            line[strcspn(line, "\n")] = '\0';

            if (line[0] == 'a')
                {
                fprintf(output, "%s ", line);
                find_arg(&argument, output);
                }
            else if (strstr(line, " f"))
                {
                fprintf(output, "%s ", line);
                find_flag_opt(&flag, line, output);/////nu vrea
                }
            else if (strstr(line, " o"))
                {
                fprintf(output, "%s ", line);
                find_flag_opt(&option, line, output);//nu vrea
                }
        }

        free_list(argument);
        free_list(option);
        free_list(flag);
        fclose(input);
        fclose(output);
        
}
else if (strcmp(argv[1], "task2") == 0) ////////////////////
{
    nod* stack = NULL;

    int recursive = 0, human_readable = 0, dir_only = 0;

    int opt;
    static struct option long_options[] = {///legaturi intre versiunea lunga si cea scurta 
        {"recursive", no_argument, 0, 'r'},
        {"human-readable", no_argument, 0, 'h'},
        {"directory", no_argument, 0, 'd'},
        {"out", required_argument, 0, 'o'},
        {0, 0, 0, 0}
    };

    char *out_path = NULL;

    while((opt = getopt_long(argc, argv, "rhdo:", long_options, NULL)) != -1) {///setare optiuni pt functii
        if (opt == 'r') {
            recursive = 1;
        } 
        else if (opt == 'h') {
            human_readable = 1;
        }
        else if (opt == 'd') {
            dir_only = 1;
        }
        else if (opt == 'o') {
            out_path = optarg;
}
    }
    FILE *output = fopen(out_path, "wt");

        if(output == NULL)//ERORCHECK
        {
            fprintf(stderr, "Error opening file\n");
            exit(EXIT_FAILURE);
        }

    util_ls(argv[optind + 1], output, &stack, recursive, dir_only,human_readable);

    freestack(stack);
    fclose(output);

}
else if (strcmp(argv[1], "task3") == 0)///////////
{
    char *ref_file = strstr(argv[argc - 1], "ref");
    if (!ref_file) //ERORCHECK
    {
        fprintf(stderr, "Last argument must contain \"ref\"\n");
        return EXIT_FAILURE;
    }
    FILE *f = fopen(ref_file, "wt");
    if (!f) //ERORCHECK
    {
        fprintf(stderr, "Error opening file %s: %s\n", ref_file, strerror(errno));
        return EXIT_FAILURE;
    }

    char *common = lcdir(argv[2], argv[3]);
    if (!common) //ERORCHECK
    {
        fprintf(stderr, "No common directory between %s and %s\n", argv[2], argv[3]);
        fclose(f);
        return EXIT_FAILURE;
    }

    Node3 *dirs = NULL;
    createroot(&dirs, common);
    free(common);
    if (!dirs) //ERORCHECK
    {
        fprintf(stderr, "Error allocating memory for root nod\n");
        fclose(f);
        return EXIT_FAILURE;
    }

    dir_tree(dirs);

    STACK *p1 = dfs_stack(dirs, argv[2]);
    STACK *p2 = dfs_stack(dirs, argv[3]);
    if (!p1 || !p2) //ERORCHECK
    {
        fprintf(stderr, "Error: could not find one of the paths in the tree\n");
        free_tree(dirs);
        fclose(f);
        return EXIT_FAILURE;
    }
    
    int steps1 = p1->top + 1;
    for (int i = 0; i < steps1 - 1; i++) {
        free(stack_pop(p1));
        fprintf(f, "../");
    }

    free(stack_pop(p1));
    stack_delete(p1);

    int steps2 = p2->top + 1;
    char **down = malloc(steps2 * sizeof *down);
    for (int i = 0; i < steps2; i++) {
        down[i] = stack_pop(p2);
    }
    stack_delete(p2);

    for (int i = steps2 - 2; i >= 0; i--) {
        fprintf(f, "%s", down[i]);
        if (i > 0) fputc('/', f);
        free(down[i]);
    }
    free(down);

    free_tree(dirs);
    fclose(f);
} 

    return 0;
}

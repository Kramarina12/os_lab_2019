#include <utils.h>

#include <getopt.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int process_options(int argc, char *argv[], struct option _options[], int size_of_options, void * _info, int is_server);

int process_options_server(int argc, char *argv[], struct ServerInfo *info)
{
    struct option options[] =
        {
            {"server-port", required_argument, 0, 0},
            {"buff-size", required_argument, 0, 0},
			{0, 0, 0, 0}
        };

    struct ServerInfo current_info;
    if (process_options(argc, argv, options, sizeof(options), &current_info, 1) != 0 )
        return 1;
    
    info->server_port = current_info.server_port;
    info->buff_size = current_info.buff_size;

    return 0;
}

int process_options_client(int argc, char *argv[], struct ClientInfo *info)
{
    struct option options[] =
        {
            {"server-port", required_argument, 0, 0},
            {"buff-size", required_argument, 0, 0},
            {"server-address", required_argument, 0, 0},
			{0, 0, 0, 0}
        };
    struct ClientInfo current_info;
    if (process_options(argc, argv, options, sizeof(options), &current_info, 0) != 0 )
        return 1;
    info->server_port = current_info.server_port;
    info->buff_size = current_info.buff_size;
    strcpy(info->server_address, current_info.server_address);
    return 0;
}


int process_options(int argc, char *argv[], struct option _options[], int size_of_options, void * _info, int is_server)
{
    int server_port = -1;
    int buff_size = -1;
    char server_address[UTILS_BUFFSIZE_ADDR] = {'\0'};

    struct option options[size_of_options];
    memcpy(options, _options, size_of_options);

    while (1) 
    {        
        int option_index = 0;
        int c = 
            getopt_long(argc, argv, "abp:", options, &option_index);

        if (c == -1) break;

        switch (c) 
        {
            case 0:
                switch (option_index) 
                {
                    case 0:
                        server_port = atoi(optarg);
                        if (server_port <= 0)
                        {
                            perror("server-port is a positive\n");
                            return 1;
                        }
                        break;

                    case 1:
                        buff_size = atoi(optarg);
                        if (buff_size <= 0)
                        {
                            perror("buff-size is a positive number\n");
                            return 1;
                        }
                        break;

                    case 2:
                        if (is_server)
                            break;
                        strcpy(server_address, optarg);

                        break;
                    default:
                        printf("Index %d is out of options\n", option_index);
                }
                break;

            case '?':
                break;

            default:
                printf("getopt returned character code 0%o?\n", c);
        }
    }
    if (optind < argc) 
    {
        perror("Has at least one no option argument\n");
        return 1;
    }

    if (server_port == -1 || buff_size == -1) 
    {
        printf("Usage: %s --server-port \"num\" --buff-size \"num\"", argv[0]);
        if (!is_server && strlen(server_address) == 0)
            printf(" --server-address \"<string ipaddress>\"");

        printf("\n");
        return 1;
    }
    
    if (is_server)
    {
        struct ServerInfo current_info;
        current_info.server_port = server_port;
        current_info.buff_size = buff_size;
        memcpy(_info, (void *)&current_info, sizeof(struct ServerInfo));
    }

    if (!is_server)
    {
        struct ClientInfo current_info;
        current_info.server_port = server_port;
        current_info.buff_size = buff_size;
        strcpy(current_info.server_address, server_address); 
        memcpy(_info, (void *)&current_info, sizeof(struct ClientInfo));

    }
    return 0;
}
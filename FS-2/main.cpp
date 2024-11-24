#include <fcntl.h>
#include <unistd.h>

#include <cerrno>
#include <iostream>

int main(int argc, char **argv)
{
    if (argc == 3)
    {
        char BUF[256];
        int sfd = open(argv[1], O_RDONLY);
        if (sfd == -1)
        {
            std::cout << "Error opening source file, code " << errno << std::endl;
            return errno;
        }

        int dfd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (dfd == -1)
        {
            close(sfd);
            std::cout << "Error opening destination file, code " << errno << std::endl;
            return errno;
        }
        int bytes_read;
        int bytes_written;
        while ((bytes_read = read(sfd, BUF, sizeof(BUF))) > 0)
        {
            bytes_written = write(dfd, BUF, bytes_read);
        }
        if (bytes_written == -1)
        {
            close(sfd);
            close(dfd);
            std::cout << "Error writing file, code " << errno << std::endl;
            return errno;
        }
        if (bytes_read == -1)
        {
            close(sfd);
            close(dfd);
            std::cout << "Error reading file, code " << errno << std::endl;
            return errno;
        }
        close(sfd);
        close(dfd);
        std::cout << "File was created successfully" << std::endl;
        return 0;
    }
    else
    {
        std::cout << "Invalid arguments, use [source file] [destination file]" << std::endl;
        return 1;
    }
}

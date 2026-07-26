#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <unistd.h> 
#include <arpa/inet.h> 
#include <ctype.h> 
#define PORT 8081 
#define BUFFER_SIZE 1024

//convert to uppercase using Ascii
void to_upper(char *str){
for(int i=0;str[i]!='\0';i++){
if(str[i]>='a' && str[i]<='z'){
str[i]=str[i]-32;
}
}
}

//convert to lowercase using Ascii
void to_lower(char *str){
for(int i=0;str[i]!='\0';i++){
if(str[i]>='A' && str[i]<='Z'){
str[i]=str[i]+32;
}
}
}

//function to reverse string
void reverse(char *str){
 int n = strlen(str); 
    for (int i = 0; i < n / 2; i++) {
        char temp = str[i];
        str[i] = str[n - i - 1];
        str[n - i - 1] = temp;
}
}
int main(){
int server_fd, new_socket;
struct sockaddr_in address;
int addrlen = sizeof(address);
char buffer[BUFFER_SIZE];
// Create socket
 server_fd = socket(AF_INET, SOCK_STREAM, 0); 
if (server_fd == 0) {
 perror("Socket␣failed");
 exit(EXIT_FAILURE);
 }
 address.sin_family = AF_INET;
 address.sin_addr.s_addr = INADDR_ANY;
 address.sin_port = htons(PORT);
 // Bind
   bind(server_fd, (struct sockaddr *)&address, sizeof(address));
 // Listen 
 listen(server_fd, 3);
printf("Server␣listening␣on␣port␣%d...\n", PORT);
 // Accept connection
 new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
 printf("Client␣connected.\n");
 while (1) {
 memset(buffer, 0, BUFFER_SIZE);
 int valread = read(new_socket, buffer, BUFFER_SIZE); 
if (valread <= 0)
 break;
 // Remove newline if present
 buffer[strcspn(buffer, "\n")] = 0;
 // Check for termination
 char command[10], text[BUFFER_SIZE];
 // Parse input
buffer[strcspn(buffer, "\n")] = '\0';

 sscanf(buffer, "%[^|]|%[^\n]", command, text);
if (strcmp(command, "UP") == 0) {
 to_upper(text);
printf("Received : %s\n", buffer);
printf("Processed: %s\n", text);
}
else if (strcmp(command, "LOW") == 0) {
 to_lower(text);
printf("Received : %s\n", buffer);
printf("Processed: %s\n", text);

 }
 else if (strcmp(command, "REV") == 0) {
 reverse(text);
printf("Received : %s\n", buffer);
printf("Processed: %s\n", text);
 }
 else { 
strcpy(text, "Invalid␣Command");
 } 
send(new_socket, text, strlen(text), 0);
 }
 close(new_socket);
 close(server_fd);
 printf("Server␣terminated.\n");
 return 0;
 }

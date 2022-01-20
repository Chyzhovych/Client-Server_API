# Viktor Chyzhovych

Project description:

Client-Server application to search directory on remote HOST.
Application support the next functionality:

1) Client has to search directory by server request.
  * client has to replay with "processing" each 500ms of searching;
  * client has to reply with success or failure.

2) Server  will request search by "directory name"
  * send success replay (include full path to the directory).

Technologies: C, Networking, Multithreading, Linux, Windows, Make.


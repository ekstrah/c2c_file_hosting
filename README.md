# Development of Client-to-Client file sharing and FTP server

Network Programming
May 24, 2018


# Introduction & Motivation

The socket is the most primitive, fundamental type provided by the operating system to communicate over the network. It’s equivalent of a file pointer for network communication. Even if you use a higher-level library for some network protocol, it is still wrapping around and managing sockets for you. So, this project is about how we can apply socket programming to real-life problem-solving.

In real life, it is cumbersome to share files with your friends because we must use either physical flash memory or need to use third-party service such as Dropbox, Gmail, I-Cloud and so on. Which has numerous disadvantage? For example; It consumes a lot of time uploading the files and downloading the files, the service provider can look at what you are storing it, and most significantly, it requires an internet connection even though your friend is sitting next to you.

So, to solve this problem of using third-party service, we have brought up an idea of Client-to-Client file sharing service. Which can be used to share files without internet connection nor won’t be spied by big brothers.
 

# Concepts and Approach


Firstly, we must be clear about how our architecture would look like. We have attached a diagram that briefly describes how it is going to work.
![Image of the file](https://i.imgur.com/qgkJtSN.png)

In words, Client will be able to share media with other Client without internet connection as long as Client is connected to a same local area network. However, if the client is on the other local area network, it requires a connection between the two in order to share media.

This will also include the “Nondivy”, Non-individual for short, sharing service, which client can share media which the must be useful to other users such as ebooks, music or even movies. All the files will be hosted on the server which can be directly downloaded from our service.

 

# Ambition & Goal


This project will help us to understand about socket programming in depth while improving our internet society. However, we will continuously add more features and improve security so that people around the world can use our service. 

Furthermore, this project is just part of a larger project of making internet freedom. We are trying to work towards to make individual’s computer as a server which can turn client to client service -> server to server operating service.

# Project Halide

HalideOS is an experimental operating system written entirely from scratch. It supports a basic shell with some commands including a command line calculator. You can boot it up in virtual box.

## Motivation

Developing an operating system from scratch is one of the hardest tasks in computer science. It is considered a pinnacle of software engineering. It requires a good grasp of low level languages, assembly language for the targetted platform, processor architecture and memory. But it is not something that undergraduate students can’t do as we learn all these subjects as a part of our coursework.

This project is an attempt by DSC KIIT to introduce students to the fascinating domain of operating systems development.


## Documentation and Download

[![Gitter](https://badges.gitter.im/project-halide/community.svg)](https://gitter.im/project-halide/community?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge)

Instructions on how to run HalideOS in Oracle VirtualBox, building HalideOS from source and other technical documentation are available at https://dsc-kiit.github.io/project-halide/

Head over to the [Releases](https://github.com/DSC-KIIT/project-halide/releases) section to download the `.iso` file.


## Tools and Languages

The bulk of HalideOS is written using C++17 with some x86 assembly code for the bootloader. These tools are easily available
for linux based operating systems via the default package manager.

* `g++`
* `as`
* `ld`
* `make`
* `qemu`


## Screenshots

Username: `<any name>`
Password: `dsc-kiit`

<div align="center">
	<img width="80%" src="https://cdn.githubraw.com/DSC-KIIT/project-halide/b06ca381/img/home.png">	
</div>


<div align="center">
	<img width="80%" src="https://cdn.githubraw.com/DSC-KIIT/project-halide/master/img/console.png">	
</div>


## Code Style

We use `clang-format` to make sure the code follows a consistent style. The details are available in the 
[.clang-format](./.clang-format) file. Most editors have features to automatically format using `clang-format`.


## License

Copyright (c) **DSC KIIT**. All rights reserved. Licensed under the MIT License

[![forthebadge](https://forthebadge.com/images/badges/built-with-love.svg)](https://forthebadge.com)
[![forthebadge](https://forthebadge.com/images/badges/made-with-c-plus-plus.svg)](https://forthebadge.com)

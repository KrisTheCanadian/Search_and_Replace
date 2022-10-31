<p align="center">
  <a href="https://github.com/KrisTheCanadian/SOEN-363-Project">
    <img src="https://upload.wikimedia.org/wikipedia/commons/1/18/C_Programming_Language.svg" height="128">
    <h1 align="center">COMP 348: Assignment 1</h1>
  </a>
</p>

<p align="center">
    <a aria-label="C" href="#">
        <img alt="" src="https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white">
    </a>
    <a aria-label="CMAKE" href="#">
        <img alt="" src="https://img.shields.io/badge/CMake-%23008FBA.svg?style=for-the-badge&logo=cmake&logoColor=white">
    </a>
    <a aria-label="Github" href="https://github.com/KrisTheCanadian/Search_and_Replace">
        <img alt="" src="https://img.shields.io/badge/GitHub-100000?style=for-the-badge&logo=github&logoColor=white" >
    </a>
    <a aria-label="markdown" href="#">
        <img alt="" src="https://img.shields.io/badge/CLion-black?style=for-the-badge&logo=clion&logoColor=white">
    </a>
</p>

# Assignment Information 🚀
"You will be writing a simple search and
replace application. Specifically, your job is to (1) find a user-specified text string within a group
of disk files, (2) modify those strings and update the original disk files, and then (3) provide a
report that indicates what has been done."

Please view the assignment instructions below for more information.

[**Assignment Instructions (PDF)**](./_docs/comp348.assignment-i.pdf)

## Running the project

```bash
mkdir build
cd build
cmake ..
make
```

or use `gcc`

```bash
gcc -Wall traversal.c text.c report.c replace.c main
```


## License 📝

This repository is available under the [MIT LICENSE](./LICENSE).

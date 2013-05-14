cog_class_wizard
================

Readme
------

This is a small code generator example written in Python useful for creation of new C++ classes. The generated code in not intended for direct compiling, but are useful for generating initial class definition files for further development.

It depends on cog, a code generation tool written in Python by Ned Batchelder, adn takes some ideas from cogflect project.

Installation
------------

1. Install Python
2. Install pip Python package manager

    On Windows:
     <python_dir>\Scripts\easy_install pip
    On Linux:
     $sudo apt-get install python-pip

3. Install cog package

    pip install cogapp

4. (optional) add the directory cog_class_wizard\generator to system path

Usage
-----

Write a yml file describing the structure of a needed C++ class place it in the generator/ directory and run the provided Python script. An sample configuration file is provided along with the code. The script reads the configuration from all .yml files on current directory  and creates the needed .cpp and .h files. 

If script directory is on system path, it is possible to run generator.py from any folder. 

Modification
------------

Non-code text, such as header and comments can be defined on files in template/ directory.
To modify the code generator, modify or add a new Python class in src/classwizard/ folder.

Licence: MIT

Alexander Granizo (2013)

		 ====================================
			Mazes for Programmers
		 Code Your Own Twisty Little Passages
		      (working through the text
			    by Jamis Buck)
		 ====================================


Introduction and Overview
-------------------------

Advent of Code exercises have a lot of mazes. Basic search and path
finding algorithms are well publicized, but this text offers a more in
depth treatment of maze creation and maze related algorithms.

The author uses Ruby, which I don't like. I'll work the text problems
in Ruby and C (compiled as c18) in parallel.

I'll be using my single header libraries for C but I don't expect
any other dependencies beyond the basic clang and make setup for MacOS.

I claim no originality here, but anything of mine in C refers back to
Buck's text and its copyrights/licenses. My implementations are
all public domain as far as I'm concerned, but you can use this
software either as public domain under the UNLICENSE or under the
terms of the MIT license. See LICENSE.txt.

Troy Brumley, blametroi@gmail.com, September 2024.

So let it be written,
So let it be done.



License
-------

Either public domain under the UNLICENSE, or MIT as you like.



Dependencies and Tooling
------------------------

This is all build on a MacBook M2 using Apple's current standard
clang. GNU make for Makefiles, include-what-you-use and astyle for
formatting and some lint picking. Other linting is done with the -Wall
-std=c18 options of clang, and with the help of eglot and clangd in my
editor.

Other than the standard libraries, my own personal single header
libraries are available at https://github.com/BlameTroi/txblibs but I
don't yet know how much they will be needed or used.



Code Notes
----------

Unlike Ruby, C is not an object oriented language, but it is possible
to think and write in it with an object oriented leaning. Class
terminology will be used frequently.

Memory management falls squarely on the shoulders of the C programmer.
As this code is geared toward learning about various maze algorithms,
some leaks may slip through. I compile with -fsanitize=address to
avoid many problems, but leaks aren't caught by the address sanitizer.

All 'object' instances will have a tag field that is used to identify
the object. When an object is explicitly released this tag is
destroyed. All 'methods' will verify the tag value via an assert
macro.

Some things are left hard coded. For example, rather than have a key
value store for linked cells, an array of four pointers is used. There
can only be four adjacent cells, one for each cardinal direction.



Ruby is not Smalltalk
---------------------

A complaint I saw in a review of this text was regarding the choice
of Ruby instead of a "mainstream" language. I think exposure to new
languages is a good thing, and was hopeful that the learning curve
would be short and gentle since I have worked with Smalltalk in the
past.

Sadly, while Ruby may look a bit like Smalltalk, it is jarringly
different. Think Bizzaro Superman different. This isn't bad per se.
I see why many like the language, but I do not.

I've made an attempt to stick to Buck's algorithms and data structures
within the constraints of writing in standard C, but this code is not
a transliteration of the Ruby and I don't know that it will help
anyone understand Ruby better. That was not a goal of this project,
but it would have been a nice outcome.



Project Layout
--------------

The text has fourteen chapters and two appendices. At the top level,
directories in_c and in_ruby have parallel structures. Directories 01
through 14, A1, and A2 are for work or files under each chapter. The
directory common will hold headers, shells, and other miscellany.

The chapter titles are given as empty files in each directory.

├── 01
│   └──  Your_First_Random_Mazes
├── 02
│   └──  Automating_and_Displaying_Your_Mazes
├── 03
│   └──  Finding_Solutions
├── 04
│   └──  Avoiding_Bias_with_Random_Walks
├── 05
│   └──  Adding_Constraints_to_Random_Walks
├── 06
│   └──  Fitting_Mazes_to_Shapes
├── 07
│   └──  Going_in_Circles
├── 08
│   └──  Exploring_Other_Grids
├── 09
│   └──  Braiding_and_Weaving_Your_Mazes
├── 10
│   └──  Improving_Your_Weaving
├── 11
│   └──  Growing_with_Prims
├── 12
│   └──  Combining_Dividing
├── 13
│   └──  Extending_Mazes_into_Higher_Dimensions
├── 14
│   └──  Bending_and_Folding_Your_Mazes
├── A1
│   └──  Summary_of_Maze_Algorithms
└── A2
    └──  Comparison_of_Maze_Algorithms

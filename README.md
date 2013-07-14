# Solutions to the [USACO Training Gateway][1] problems

This repository contains solutions to the USACO Training Gateway problems,
available at [http://ace.delos.com/usacogate][1]. These solutions are provided
"as is". I give no guarantees that they will work as expected. Submitting my
solutions will probably get you banned from the USACO website.

## Instructions

You can compile all the problems by issuing the following command:

    $ make

If you want to compile only a specific problem, issue the following command,
replacing `<problem_id>` with the id of the problem you want to compile (see
section "Problems Solved" for the list of possible ids):

    $ make <problem_id>

Running a compiled problem is just a matter of executing a command similar to
the next one, replacing `barn1` with the id of the desired problem:

    $ ./barn1

Remember that each problem expects its input in a file with a `.in` extension in
the directory the binary is executed from and with name equal to the problem id,
and outputs its result to a file with a `.out` extension and with name equal to
the problem id.

## Problems solved

The following is the list of the problems solved. Each problem id is specified
between round brackets. I would like to have links to the problem statements,
but the usaco site doesn't make it easy to get permalinks, by requiring a GET
parameter after authentication, and by not redirecting after login.

### Section 1.0

* Test (`test`)

### Section 1.1

* Your Ride is Here (`ride`)
* Greedy Gift Givers (`gift1`)
* Friday the Thirteenth (`friday`)
* Broken Necklace (`beads`)

### Section 1.2

* Milking Cows (`milk2`)
* Transformations (`transform`)
* Name That Number (`namenum`)
* Palindromic Squares (`palsquare`)
* Dual Palindromes (`dualpal`)

### Section 1.3

* Mixing Milk (`milk`)
* Barn Repair (`barn1`)
* Calf Flac (`calfflac`)
* Prime Cryptarithm (`crypt1`)

### Section 1.4

* Packing Rectangles (`packrec`)
* The Clocks (`clocks`)
* Arithmetic Progressions (`ariprog`)
* Mother's Milk (`milk3`)

### Section 1.5

* Number Triangles (`numtri`)
* Prime Palindromes (`pprime`)
* SuperPrime Rib (`sprime`)
* Checker Challenge (`checker`)

### Section 2.1

* The Castle (`castle`)
* Ordered Fractions (`frac1`)
* Sorting a Three-Valued Sequence (`sort3`)
* Healthy Holsteins (`holstein`)
* Hamming Codes (`hamming`)

### Section 2.2

* Preface Numbering (`preface`)
* Subset Sums (`subset`)
* Runaround Numbers (`runround`)
* Party Lamps (`lamps`)

### Section 2.3

* The Longest Prefix (`prefix`)
* Cow Pedigrees (`nocows`)
* Zero Sum (`zerosum`)
* Money Systems (`money`)
* Controlling Companies (`concom`)

### Section 2.4

* The Tamworth Two (`ttwo`)
* Overfencing (`maze1`)
* Cow Tours (`cowtour`)
* Bessie Come Home (`comehome`)
* Fractions to Decimals (`fracdec`)

### Section 3.1

* Agri-Net (`agrinet`)
* Score Inflation (`inflate`)
* Humble Numbers (`humble`)
* Shaping Regions (`rect1`)
* Contact (`contact`)
* Stamps (`stamps`)

### Section 3.2

* Factorials (`fact4`)
* Stringsobits (`kimbits`)
* Spinning Wheels (`spin`)
* Feed Ratios (`ratios`)
* Magic Squares (`msquare`)
* Sweet Butter (`butter`)

### Section 3.3

* Riding the Fences (`fence`)
* Shopping Offers (`shopping`)
* Camelot (`camelot`)
* Home on the Range (`range`)
* A Game (`game1`)

### Section 3.4

* Closed Fences (`fence4`)
* American Heritage (`heritage`)
* Electric Fence (`fence9`)
* Raucous Rockers (`rockers`)

### Section 4.1

* Beef McNuggets (`nuggets`)
* Fence Rails (`fence8`)
* Fence Loops (`fence6`)

[1]: http://ace.delos.com/usacogate

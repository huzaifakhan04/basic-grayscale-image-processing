# Basic Greyscale Image Processing:

This repository is a collection of fundamental image processing operations and algorithms performed on greyscale images, or Portable Grey Map (PGM) files, using different data structures in C++, as part of an assignment module for the Data Structures (CS2001) course.

## Introduction:

Digital image processing (or image processing) uses a digital computer to process digital images through an algorithm. As a subcategory or field of digital signal processing, digital image processing has many advantages over analogue image processing. It allows a much wider range of algorithms to be applied to the input data and can avoid problems such as the build-up of noise and distortion during processing. Since images are defined over two dimensions (perhaps more), digital image processing may be modelled as a multidimensional system.

### What Are Portable Grey Map (PGM) Files?

Portable Grey Map (PGM) files store greyscale two-dimensional images. Each pixel within the image contains only one or two bytes of information (8 bits or 16 bits). While that might not sound like a lot of information, PGM files can hold thousands of shades — from pure black to white and every shade of grey in between.

Furthermore, saving a two-dimensional array in a programming language like C++ as an image file in a Portable Network Graphics (PNG), Joint Photographic Experts Group (JPEG), or any other format would require a lot of effort to encode the data in the specified format before writing to a file. For this reason, the Portable Grey Map (PGM) format offers a simple solution that allows for human readability and easy portability.

## Implementation:

*  Create a class for storing the Portable Grey Map (PGM) file information and allocate memory for the same.
*  Open the Portable Grey Map (PGM) file in a binary format.
*  Extract the pixel information, which can then be used for further processing.
*  Separate the header information into discrete variables defined within the code.
*  Store the pixel information in a two-dimensional array defined within the code for image processing operations.
*  Compute elementary information about the Portable Grey Map (PGM) file (greyscale image).
*  Extract the connected components from the Portable Grey Map (PGM) file using a Connected-Component Labelling (CCL) algorithm (implemented using both the queue and stack data structure individually).
*  Save the connected-component labelled file as an independent Portable Grey Map (PGM) file.

## Instructions (Execution):

In the ``Images`` folder, there are multiple Portable Grey Map (PGM) files that can be analysed using this module. Just copy the path to any of those (or any other) Portable Grey Map (PGM) files, and paste it next to ``InputFile=`` in ``Main.cpp``. After that, run the code normally and choose any of the presented options to analyse the particular greyscale image accordingly.

* **QUESTION #1** — Compute elementary information about the Portable Grey Map (PGM) file (greyscale image).
* **QUESTION #2** — Extract the connected components from the Portable Grey Map (PGM) file using a Connected-Component Labelling (CCL) algorithm (implemented using the queue data structure).
* **QUESTION #3** — Extract the connected components from the Portable Grey Map (PGM) file using a Connected-Component Labelling (CCL) algorithm (implemented using the stack data structure).

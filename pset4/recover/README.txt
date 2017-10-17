/*
Pseudo

1) Open memory card file

2) Find beginning of JPEG

3) Open new JPEG

4) Write 512 bytes until new JPEG is found

5) Detect end of file



*/


/*

Code snippets given in Walkthrough


Conditional to identify the beginning of a JPEG

    if (buffer[0] == 0xff &&
        buffer [1] == 0xd8 &&
        buffer [2] == 0xff &&
        (buffer [3] & 0xf0) == 0xe0 )


Name new files automatically

    sprintf(filename, "03i%.jpg", 2)

        filename: char array to store resultant string
            002.jpg

    FILE * img = fopen(filename, "w");




*/





Rubber duck talk


1) TODO: Hexidecimals per byte
    A hexidecimal is stored in 4 bits. That means each byte contains two hexidecimal digits.
        What does that mean for how I access the hexidecimals?

    Is there only one hexidecimal in each byte, leaving extra space for ______?
            If yes, then I would look at each byte of the block of memory, 512 of them, to copy that memory over to a new block of memory.


2) DONE: BYTES of memory in a block
    How many bytes are in a block of a memory card?
        512

    Then I should one block over at a time. Each time I would check to see if it was the start of a new JPEG,
    or the end of the file. until I got to the end of the jpg files.

    Start of new JPG, means save to a new file.

    End of the file, means no more JPGs to be found and I can close everything.

    Note: The end is indicated by a block of memory that does not contain 512 bytes.

3) TODO: Pointers and Dynamic Memory:

   Dynamic memory, malloc, only give back a pointer to a chunk of memory of specified size.

   Once the pointer is given back, data has to be stored into the allocated memory.

   This has to happen before I can look up values stored at a particular memory location.
        (e.g. &block[_] requires me to have stored a value in the memory at block.)

    To store values at the memory pointed to by _______ pointer, do I need to dereference the pointer?

4) TODO: Where in the stream to begin reading memory card

    I think I have to skip the first 512 bytes, first block, of memory.


5) TODO: How to name a file automatically



CODE:

    sprintf(filename, "03i%.jpg", 2)

        filename: char array to store resultant string
            002.jpg

    FILE * img = fopen(filename, "w");

NOTES:




QUESTIONS:

    Q: Does sprintf initialize the character array, "filename," or do I have to initalize char array filename before sprintf() first?
    A: I think I have to initialize filename with char * filename = malloc(8);
        size 8 because    0, 0, 0, ., j, p, g, \0    is 8 characters

        In this case filename will be a pointer to the 8 bytes of memory,
        where a particular iteration of filename is stored

                       [0] [1] [2] [3] [4] [5] [6]  [7]
        *filename --->  _   _   _   _   _   _   _   \0

        &filename is the address of the pointer, filename (e.g. 081ebf9).

        The pointer, filename, is different than the memory stored in the 8 bytes of memory, which filename points to.

        filename = pointer

        The 8 bytes of memory allocated by malloc(8), does not have a name/label yet.

        I could create a variable to store a file name in. However, that is not necessary with sprintf(),
        becuase it writes straight to the bytes of memory pointed to by filename.


        int sprintf(char * str, const char * format, ...);

        sprintf() writes output to the character string, str.


        Therefore if I pass in the format "03i%.jpg", which inputs jpgctr into the integer value,
        then sprintf will write it's output to the character string, filename.

        This only works if there is a character string called filename.
        Therefore, I need to initialize the char* object, filename beforehand.




    Q: When I create a pointer to a file, named with whatever is stored in filename, what do I do with that pointer?
    A:


    Q:  FILE * img = fopen(filename, "w");

        Does this open a file, named filename.
        Does it use the character array in "filename" to open a file, with the same name of the value stored in the filename char array?
        If filename starts are a char array, then how am I opening a FILE in write mode?
        Are we transforming a char array into a file, by saying a file is stored at &img?

    A: I thinkkk.... we have essentially stored a value like, "002.jpg" into the char array variable, "filename".
        When I fopen, "filename," I essentially open a file with the name, "002.jpg,"
        then, it is in write mode,
        from there, I can access 002.jpg by fwrite()'ing to img, from the buffer.

            img can be the pointer to the file
            e.g. FILE * img = fopen(filename, "w");


    Q: What is the difference between an (&) operator and a pointer (*)?
    A: & is a address extraction operator. (&) gives you the pointer-to-object.
        &arr[i] gives you the address of the i'th character where arr is stored. Effectively it gives you the pointer to that place.
        This is used in the context of figure out where to read to, or write from, in files. For functions like fread and fwrite, you want to know the place at which to store values when reading, or where to find the values you want to write to a new file.
        You do not actually give fread or fwrite the value you want, but the location of the value you want, so it can do the work for you.

    * is a dereference operator. int * p = 27 creates a pointer 'p' which is the address of an integer object of value 27.
        When we use *p = 28, we say look at pointer 'p', then go to the location 'p' points to, at that location there is a value of 27.
        Change 27 to 28.

        & is helpful because it tells us where something is in memory.
        However, knowing where something is in memory does not mean we are interacting with it.
        * affords us the ability to interact with the information at the location.

    Q: What should you store in the memory pointed to by a pointer if you are not sure what you want store there yet? Why?
    A: You should store NULL in any new pointers you declare, if you are not going to set it to anything else.
        This is because the program will give you a segmentation fault when you try to reference a NULL pointer.
        The segmentation fault will halt your program. It is better you have your program halt, than it is to accidentally overwrite important memory.
        If you declare a pointer without setting it to anything, then it will arbitrarily choose a piece of memory which could be important to your computer.
        Therefore, when the pointer is derefenced in your program you would be dereferencing important data.
        Setting your pointer to NULL avoids this issue.

    Q: If we know their are jpegs stored on the memory card file, but do not know how large the jpeg will be,
        then how do we know in advance, how much memory to allocate?

        Do we allocate memory the size of the memory card each time we want to save a file?
        Wouldn't that mean we allocate way, way more memory than we need?

        If yes, what do we do with that extra memory? How can we free, only the extra memory.

    A: If we allocate temporary memory in the form of a buffer, then we can allocate buffer memory the size of the memory card file,
        Once we are sure we have collected all the information in a jpg image, then we could write from the buffer to the new jpg file.

        Then we can either free the memory, if we have reached the end of the memory card file.
        Otherwise, we can clear and re-use the memory to temporarily store the next jpg image.

    A2: Actually, we can allocate our temporary memory 1 block at a time, then write that block into a file one at a time.
        This way we only have to use 512 bytes of memory (actually, we probably need more of that to move things around, but you get the point)



    Q: How do we clear the memory stored in a temporary storage variable, buffer?
    A: We might either be able to set *buffer = NULL;
        Or, set *buffer = 0;
        Or, free(buffer);
        Then allocate the memory to buffer on the next loop.

        The last option is the most likely to work. I am not sure if *buffer = 0;
        will reset every byte of memory to 0, or oly the first.
        Probably all, but I am not sure

        For the first *buffer = NULL; I am not really sure what NULL does.
        Does it move the pointer to a seperate area?
        Does it reset the current memory block to zero?
        Does it put some kind of label, "NULL" over what is already there.
        The most logical option seems to be that we set the pointer to "no where"
        Therefore, when we derefence the pointer to point to a new stored value, 000.jpg,
        then it would find new memory to store the image.
        However, if we set the pointer = to NULL,
        then do we need to reallocate memory of a particular size,
        or does the pointer remember what size of memory it needs to point to?
        We would probably need to reallocate the correct size of memory, because if the pointer moves from that initial memory block,
        I doubt it somehow saved the size of that memory. In fact, I am almost 100% sure it would not, because I do not think it saves the size in the first place.
        Rather it finds a memory block the size of malloc(), then stays pointing at that until we need it. It knows nothing about numbers.
        Therefore, if we dereference the pointer so it points to NULL, then we need to dereference it again, to a block of allocated memory.


    Q: How does one create a hexidecimal data type?
    A: Data types include int and char, but integers are 4 bytes, 16 bits. Whereas, hexidecimals take up 4 bits, half a byte.
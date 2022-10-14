# CLI_Photoshop

This project represents an "image editor" in C for [ppm and pgm images](http://paulbourke.net/dataformats/ppm/). This
image editor allows you to edit one image at the time; after you load it, you
have to "select" the part of the image that you want to change. Then you can
perform different actions on that section: rotate, apply an effect, crop and
at the end you can save your edited photo.

## Need to know

This program is doing basically matrix operations. So, the image will be seen 
as a matrix of pixels, where the upper left pixel is the first element in the 
matrix ([0][0]), and the lower right one is the last element in the matrix 
([w - 1][h - 1], where ***w*** is the number of pixels on the width and ***h*** is 
the number of pixel on the height of the image). When selecting a part of the 
image, there will be needed 4 coordinates: x1, x2 in [0, w], and y1, y2 in [0, h]. 
When applying an efect, cropping or rotating the selected part, the changes will 
be made only for the pixels in the range [x1, x2) * [y1, y2) (this is because 
we see the image as a matrix that has the indices in the range [0, w - 1] and [0, h - 1]).


### LOAD

-> loads in memory the photo that will be edited (if you already have an image loaded, the new one will take its place and the changes in the old image will be discarded)

-> after the loading process is done, the whole image will be selected

Usage:

LOAD photo.ppm


### SELECT

This functionality allows you to choose between:

-> selecting a part of the image using the given coordinates (x1, y1, x2, y2, 
with 0 <= x1 < x2 <= l and 0 <= y1 < y2 <= h); if the coordinates are invalid 
or the number of arguments is less than four, an error mesage will be displayed

Usage:

SELECT 0 200 500 700

(selected pixels in the range [0, 500) * [200, 700) )

-> selecting all the pixels of the image

Usage:

SELECT ALL


### APPLY

-> this functionality applies to the selected part of the image differnet 
effects (edge, sharpen, blur or gaussian_blur) using an [image kernel](https://en.wikipedia.org/wiki/Kernel_(image_processing))

-> it only works for the rgb photos

-> it requires one of the following arguments: EDGE, BLUR, SHARPEN, GAUSSIAN_BLUR; 
if the argument is inexistent or an invalid one, an error message will be displayed

Usage:

APPLY SHARPEN


### ROTATE

-> rotates only if the selected area is square or the entire image is selected

-> it requires an argument (the angle of rotation) that can have one of the following values: 
-360, -270, -180, -90, 0, 90, 180, 270, 360

Usage:

ROTATE 90


### CROP

-> it crops the selected part of the image; after the process is done, the whole 
new image will be selected

Usage:

CROP


### SAVE

-> this functionality will save the modified image either in text or binary file.

-> the first argument needs to be the name of the saved file; if you want it 
to be saved in a text file, you will need to add the argument "ascii"

Usage:

SAVE editedphoto.ppm

SAVE editedphoto.pgm ascii


### EXIT

-> exits the program and frees all the resources used

Usage:

EXIT






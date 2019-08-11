#!usr/bin/python3

import numpy as np
"""
Implementing two tests: One which notices if the initial rectangle is
entirely outside of the mandelbrot set, and another which does not say
that the rectangle is outside if it is inside.
"""

#Need to check if all elements in the array picture[:][:] are equal. That means that its either entirely
#inside or entirely outside of the Mandelbrot set. IF it is entirely inside, it will also follow that the
#modulouses of all corners are less than two.

def test_rect_outside(xmin, xmax, ymin, ymax):
    #Need to check all four corners for the case of all four quadrants around the origin:
    q1 = np.sqrt(xmin**2 + ymin**2)
    q2 = np.sqrt(xmax**2 + ymin**2)
    q3 = np.sqrt(xmax**2 + ymax**2)
    q4 = np.sqrt(xmin**2 + ymax**2)
    #If all these corners are outside of the circle with radius 2, then the rectangle is outside.
    q = not (q1>2 and q2>2 and q3>2 and q4>2) #Need "not" so that assert notices when it's outside.
    msg = "Value error: Initial points chosen produce a rectange which is not within the Mandelbrot set."
    assert q, msg

    """
    condition = np.unique(picture).size
    if condition==1: #if all colors are equal (can be the case inside and outside)
        #If all values equal zero, it is entirely outside.
        msg = "Value error: Initial points chosen produce a rectange which is not within the Mandelbrot set."
        assert picture.all() == 0, msg
    """




def test_rect_inside(xmin, xmax, ymin, ymax, max_escape_time, picture):
    #Need to check all four corners for the case of all four quadrants around the origin:
    q1 = np.sqrt(xmin**2 + ymin**2)
    q2 = np.sqrt(xmax**2 + ymin**2)
    q3 = np.sqrt(xmax**2 + ymax**2)
    q4 = np.sqrt(xmin**2 + ymax**2)
    #If all these corners are outside of the circle with radius 2, then the rectangle is outside.
    q = not (q1>2 and q2>2 and q3>2 and q4>2) #Need "not" so that assert notices when it's outside.
    msg = "Value error: Initial points chosen produce a rectange which is not within the Mandelbrot set."
    assert q, msg
    #If the program get here, then the rectangle is somewhat inside the mandelbrot set.
    #See no other way to check if the values are entirely inside the set after zero iterations..
    #This test is therefore run after the calculation as opposed to the first test.
    #If all the values are equal to the max_escape_time, then the picture is entirely inside the mandelbrot set.
    #Check this in the following fashion:

    condition = np.unique(picture).size
    if condition==1: #if all values are equal (can be the case inside and outside)

        msg = "Value error: Initial points chosen produce a rectange which is entirely within the Mandelbrot set."
        #"If all points are not equal to zero, the rectangle is within the Mandelbrot set."
        assert picture.all() != max_escape_time, msg

#This exercise unfortunately was confusing and ambiguous.

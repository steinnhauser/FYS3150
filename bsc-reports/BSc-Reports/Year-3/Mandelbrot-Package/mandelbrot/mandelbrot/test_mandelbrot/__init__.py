from .test_mandelbrot import test_rect_outside
from .test_mandelbrot import test_rect_inside

def test_init_rect_inside(xmin, xmax, ymin, ymax, max_escape_time, picture):
    test_rect_inside(xmin, xmax, ymin, ymax, max_escape_time, picture)

def test_init_rect_outside(xmin, xmax, ymin, ymax):
    test_rect_outside(xmin, xmax, ymin, ymax)

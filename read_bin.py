#!/usr/bin/env python

import numpy as np
import matplotlib.pyplot as plt
import sys 

with open(sys.argv[1], "r") as f:
	raw = np.fromfile(f, dtype=np.uint8)

im = raw.reshape((320,512,3))

print im.shape

plt.imshow(im)
plt.tight_layout()
# plt.colorbar()
plt.show()

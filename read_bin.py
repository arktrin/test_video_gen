#!/usr/bin/env python

import numpy as np
import matplotlib.pyplot as plt

with open("fb_dump.bin", "r") as f:
	raw = np.fromfile(f, dtype=np.uint8)

im = raw.reshape((320,512,3))

print im.shape

# raw_sum = np.zeros(512*320)
# im = np.zeros((512, 320))
# c = 0

# for i in xrange(0, raw.shape[0], 3):
#	raw_sum[c] = np.sum(raw[i:i+3]) 
#	c += 1

# im = raw_sum.reshape((320,512))

plt.imshow(im)
plt.colorbar()
plt.show()

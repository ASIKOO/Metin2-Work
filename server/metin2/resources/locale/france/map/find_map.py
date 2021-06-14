import os
import sys

rectList = []
for line in open("index"):
	path = line.split()[1]
	if path[-1] == os.linesep:
		path = path[:-1]

	for line2 in open(path + "/" + "Setting.txt"):
		tokens = line2.split()
		if not tokens:
			continue

		if tokens[0] == "BasePosition":
			x, y = [int(item) / 100 for item in tokens[1:3]]
		elif tokens[0] == "MapSize":
			w, h = [int(item) * 256 for item in tokens[1:3]]

	rectList.append((path, x, y, x+w, y+h))

x = int(sys.argv[1])
y = int(sys.argv[2])
for rect in rectList:
	if x >= rect[1] and y >= rect[2] and x <= rect[3] and y<= rect[4]:
		print rect[0]

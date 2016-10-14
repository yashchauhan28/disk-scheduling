dict1 = {}
list1 = []
all = str(raw_input())
list1 = all.split(' ')
print list1
for each in list1:

 	if(each in dict1.keys()):

 		dict1[each] += 1
 	else:
 		dict1.update({each:1})
for each in dict1:
	if(dict1[each] >=2):
		print each , " " , dict1[each]
# This is an advanced example of usage of the packet filter in conditional attacks.
#
# usage: 
#  python ../interpreter/interpreter.py -i advanced-packet-filter-2.asl -o advanced-packet-filter-2.xlm
# 
# author: Francesco Racciatti <racciatti.francesco@gmail.com>

# declare and initialize a list of nodes
list targetList = {1}

# conditional attack statement (starts at 100 and it refers nodes in targetList)
from 100 nodes in targetList do {

	# packet filter, it filters all packets having the field 'sequenceNumber' as a perfect multiple of 3.
	filter(("APP.sequenceNumber" % 3 ) == 0)
		
		# drop the (original) intercepted packet
		drop(original, 1)
    
}

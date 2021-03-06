# This is an example of ASL file that contains two conditional attacks.
# A conditional attack is a statement that contains a *packet-filter* and a 
# set of logical primitives (clone, create, drop, put, change, retrieve, send).
# The packet-filter filters all the packet passing throught the nodes contained in the list *list* from time *time*.
# The logical primitives are executed only if an intercepted packet matches with the packet-filter.
#
# usage: 
#  python ../interpreter/interpreter.py -i conditional-attacks.asl -o conditional-attacks.xlm
# 
# author: Francesco Racciatti <racciatti.francesco@gmail.com>

# declare and initialize lists of nodes
list targetList = {1,2,3}
list dstList = {4,5,6}
list dropList = {7,8}

# conditional attack statement (starts at 100 and it refers nodes in targetList)
from 100 nodes in targetList do {

	# packet filter, it filters all packets having the field 'sourcePort' of the layer 'NET' equals to 1000
	filter("NET.sourcePort" == 1000)
		
        # change the packet content
        change(original, "APP.data", 2500)
        
		# put the original intercepted packet in the RX buffer of nodes in the dstList without update stats and with delay 0.5 ms
		put(original, dstList, RX, FALSE, 0.5)
 
}


# conditional attack statement (starts at 100 and it refers nodes in targetList)
from 100 nodes in targetList do {

	# packet filter, it filters all packets having the field 'sourcePort' of the layer 'NET' equals to 1000
	filter("APP.snNumber" > 1000)
		
		# drop put the original intercepted packet
		drop(original, 1)
 
}

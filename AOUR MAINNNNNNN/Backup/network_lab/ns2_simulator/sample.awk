sample.awk


BEGIN {
print "performance evaluation"
send=0
recv=0
dropped=0
rout=0
}
{
if($1=="+" && $3=="0"||"1" && $5=="cbr")
{
send++
}
if($1=="r" && $4=="5" && $5=="cbr")
{
recv++
}
if($1=="d")
{
dropped++
}
if($1=="r" && $5=="rtProtoLS")
{
rout++
}
}
END{
print "No of packets Send:"send
print "No of packets Received:"recv
print "No of packets dropped:" dropped
print "No of routing packets:"rout
NOH=rout/recv
PDR=recv/send
print "Normalised overhead:" NOH
print "Packet delivery ratio:"PDR
}
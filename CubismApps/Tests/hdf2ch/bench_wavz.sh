TEST=$1
DATE=`date +%Y-%m-%d:%H:%M:%S`
LOG=/tmp/${DATE}.`echo ${TEST#./} | tr " " "-" `log.txt
#RES=wavz_${DATE}.`echo ${TEST#./} | tr " " "-" `_res.txt
#RES=wavz_`echo $2 | tr " " "-" `_res.txt
RES=`echo $2 | sed 's/\// /g' | awk '{print $NF}'`_wavz_res.txt
#echo $RES
 
for PARAM in 0.000001 0.000010 0.000100 0.001000 0.010000 0.100000 1.000000  5 10 20 30 50 75 100 
do
    echo "TEST with PARAM=$PARAM"
    echo "LOG AT $LOG"
    $TEST $2 $PARAM
done | tee $LOG

cat $LOG | egrep "RES" | tee $RES
#cat $LOG | egrep "RES" | tee last-results.txt
#cat $LOG | egrep "RES" | awk '{ print $2, $4, $6, $8}' | tee last-results.txt


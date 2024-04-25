num_tests=5

for i in $(seq 1 $num_tests)
do
    ../BS3/zeiten ./sort && ../BS3/zeiten ./sort a
    echo "-------------------------"
done
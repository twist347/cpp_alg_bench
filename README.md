## std algs benchmark demo

requirements: C++-20, google test, google benchmark, tbb, openmp


plotly for plotting (python)

perf tests in test_bench dir

accuracy tests of custom algs in test_accuracy dir (with address, undefined and leak sanitizers)

## algs:
    copy
    sort
    map
    zip
    reduce
    inner product
    partial sum

## plotting via plotly:
./generate_csv.sh ./executable -> benchmark.csv


python plot_plotly.py -f ./benchmark.csv

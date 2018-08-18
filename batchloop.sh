#!/bin/bash -l

while IFS='' read -r line || [[ -n "$line" ]]; do
    echo "Text read from file: $line"
    sbatch /nas/longleaf/home/cbartram/Caliope_Analysis/AnalysisCodeApril2018/batch.sh $line $line
done < "$1"                                                    

# run the analysis command   

script_dir=$(dirname ${0})

echo "Running PMD..."

${script_dir}/pmd-bin-5.7.0/bin/run.sh pmd -dir $1 \
  -f html -version 1.8 -language java \
  -rulesets java-basic,java-design > pmd.html

echo "Please checkout pmd.html for results"

echo "Running checkstyle"

java -Dsuppressions=${script_dir}/suppressions.xml\
     -jar ${script_dir}/checkstyle-7.8.2-all.jar \
     -c ${script_dir}/checkstyle-coursera.xml \
     $1/*.java

echo "Running findbugs"

${script_dir}/findbugs-3.0.1/bin/findbugs \
             -home ${script_dir}/findbugs-3.0.1/ \
             -textui -include ${script_dir}/findbugs-coursera.xml \
             -sourcepath $1 \
             -auxclasspath ${script_dir}/stdlib.jar \
             $1/*.class

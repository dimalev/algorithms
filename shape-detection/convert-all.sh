for type in box triangle circle ellipse
do
    for file in `find $type/ -iname \*.png`
    do
        if [ ! -e ${file/png/txt} ]
        then
            python convert.py ${file} ${file/png/txt}
        fi
    done
done

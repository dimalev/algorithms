for type in box triangle circle ellipse
do
    for file in `find $type/ -iname \*.txt`
    do
        echo "testing $file"
        output=$(python image.py < $file)
        if [ "$output" != "$type" ]
        then
            echo "[E] $file failed"
        fi
    done
done


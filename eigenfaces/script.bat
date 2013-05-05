echo hi
main --eigenfaces 10 25 25 neutral/list.txt neutral.face
main --constructuserbase neutral.face neutral/list.txt neutral.user
for %%A in (interesting/*.tga) do (main --recognizeface interesting/%%A neutral.user neutral.face 1)
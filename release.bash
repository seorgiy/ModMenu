
MOD_NAME="ModMenu"

REPOSITORY_ADDRESS=$(git config --get remote.origin.url | sed 's/.*\/\([^ ]*\/[^.]*\).*/\1/')
CURRENT_COMMIT=$(git rev-parse HEAD)
CURRENT_DATE=$( date +%d.%m )
TARGET_DIR="./release"

echo "Clearing..."
if [ -d "$TARGET_DIR" ]; then
    shopt -s dotglob
    rm -rf "$TARGET_DIR"/*
else
    echo "folder $TARGET_DIR not found."
fi

echo "Pulling..."
git clone git@github.com:$REPOSITORY_ADDRESS.git release

echo "Removing..."
mv release/mod modTEMP
shopt -s dotglob
rm -rf "$TARGET_DIR"/*
mv modTemp/* "$TARGET_DIR"/
rm -d modTemp

echo "Setting version file..."
cp version.txt "$TARGET_DIR"/${MOD_NAME}_${CURRENT_DATE}_${CURRENT_COMMIT}.txt

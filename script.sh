#!/bin/bash
echo ""
echo "------------------INVALID------------------"
echo ""
echo ""

for file in maps/invalid/color/*; do
    if [ -f "$file" ]; then
        filename=$(basename "$file")
        echo "=== Test avec $filename ==="
        ./cub3D "$file"
        echo ""
        echo ""
    fi
done

for file in maps/invalid/file/*; do
    if [ -f "$file" ]; then
        filename=$(basename "$file")
        echo "=== Test avec $filename ==="
        ./cub3D "$file"
        echo ""
        echo ""
    fi
done

for file in maps/invalid/map/*; do
    if [ -f "$file" ]; then
        filename=$(basename "$file")
        echo "=== Test avec $filename ==="
        ./cub3D "$file"
        echo ""
        echo ""
    fi
done

for file in maps/invalid/texture/*; do
    if [ -f "$file" ]; then
        filename=$(basename "$file")
        echo "=== Test avec $filename ==="
        ./cub3D "$file"
        echo ""
        echo ""
    fi
done

for file in maps/invalid/trash/*; do
    if [ -f "$file" ]; then
        filename=$(basename "$file")
        echo "=== Test avec $filename ==="
        ./cub3D "$file"
        echo ""
        echo ""
    fi
done

echo "------------------VALID------------------"
echo ""
echo ""

for file in maps/valid/*; do
    if [ -f "$file" ]; then
        filename=$(basename "$file")
        echo "=== Test avec $filename ==="
        ./cub3D "$file"
        echo ""
        echo ""
    fi
done
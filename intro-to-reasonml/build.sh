#!/bin/bash
set -ev
cd ./intro-to-reasonml
npm install --production
cp ./html.js ./node_modules/mdx-deck/lib/html.js
npm run build
cp -r ./dist ../out/intro-to-reasonml
cd ../
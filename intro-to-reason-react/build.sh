#! /bin/bash

set -ev
cd ./intro-to-reason-react
npm install --production
cp ./html.js ./node_modules/mdx-deck/lib/html.js
npm run build
cp -r ./dist ../out/intro-to-reason-react
cd ../
#! /bin/bash

set -ev
cd ./intro-to-reason-react
npm install --production
npm run build
cp -r ./dist ../out/intro-to-reason-react
cd ../
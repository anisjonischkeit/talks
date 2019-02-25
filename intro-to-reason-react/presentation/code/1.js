let data = null;

fetch("http://gimme-the-goods.com/api")
.then(res => res.json())
.then(json => {
    data = json;
});
var express = require('express');
var app = express();
var path = require('path');
var yaml = require('yamljs');
var jsonParser = require('body-parser').json();

var port = process.env.PORT || 3000;

var subreddits = [];

var lineReader = require('readline').createInterface({
    input: require('fs').createReadStream('big_subreds.txt')
});

lineReader.on('line', function (line) {
    subreddits.push(line);
});

app.use(express.static(__dirname + '/public'));

app.get('/', function(req, res) {
    res.sendFile(path.join(__dirname + '/index.html'));
});

app.get('/search', function(req, res) {
    res.send(subreddits);
})

app.post('/reddit', jsonParser, function (req, res) {
    const { execFile } = require('child_process');
    var stream = require('stream');
    const child = execFile('./store_reddit', req.body.args, function (error, stdout, stderr) {
        // if (error) console.log(error);
        // if (stderr) console.log(stderr);
        // console.log(stdout);
        res.send(yaml.parse(stdout));
    });

    var stdinStream = new stream.Readable();
    var subreddits = req.body.subreddits;
    for (var i = 0; i < subreddits.length; i++) {
        stdinStream.push(subreddits[i] + '\n');
    }
    stdinStream.push(null);
    stdinStream.pipe(child.stdin);
});

app.listen(port);

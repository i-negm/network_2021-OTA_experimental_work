const express = require('express')
const fs = require('fs');
const app = express()
const port = 80

download = function (data, filename, mimetype, res) {
  res.writeHead(200, {
      'Content-Type': mimetype,
      'Content-disposition': 'attachment;filename=' + filename,
      'Content-Length': data.length
  });
  res.end(Buffer.from(data, 'binary'));
};

app.get('/version', (req, res) => {
  res.send('v3.3.0!')
})

app.get('/fetch', (req, res) => {
  var buffer;
  
  fs.readFile('./TestOTA.ino.esp32.bin', 'utf8', function (status, fd) {
    if (status) {
      console.log(status.message);
      return;
    }
    download(fd, 'TestOTA.ino.esp32.bin', 'application/octet-stream', res)
      console.log(fd.length);
    });

    //console.log(buffer)
    // download(buffer, 'TestOTA.ino.esp32.bin', 'application/octet-stream', res)

  });



app.listen(port, () => {
  console.log(`Example app listening at http://localhost:${port}`)
})
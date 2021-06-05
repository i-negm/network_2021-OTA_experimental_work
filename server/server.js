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
  const requestName = '/fetch';
  const fileName = "./TestOTA.ino.esp32.bin";
  // Get length of the application.bin
  const fileSize = fs.statSync(fileName).size;

  console.log(`[DEBUG:${requestName}] Opening fileName:${fileName}, fileSize:${fileSize}...`);
  
  fs.open(fileName, 'r', function (status, fd) {
    
    // Check if opened successfully
    if (status) {
      console.log(`[ERROR:${requestName}] Failed to open:${fileName}`);
      console.log(status.message);
      return;
    }
    
    // Send the file data
    buffer = Buffer.alloc(fileSize);
    fs.read(fd, buffer, 0, fileSize, 0, function (err, num) {
    });
    
    console.log(`[DEBUG:${requestName}] Embed file:${fileName} in HTTP response...`);
    download(buffer, fileName, 'application/octet-stream', res);
    console.log(`[DEBUG:${requestName}] Response with file:${fileName} successful.`);
  });
  
})

app.listen(port, () => {
  console.log(`Example app listening at http://localhost:${port}`)
})
import express from 'express'
const router = express.Router();
const http = require('http');

let pi_server_Url = {
    hostname: '192.168.0.9',
    port: '3000',
    path : '/Aircleaner_Control/'
};

/* GET home page. */
router.post('/power', (req, res, next) => {
    const aa = {};
    console.log('aircleaner power');
    pi_server_Url.path += "power";
    http.request(pi_server_Url).end();
    console.log(pi_server_Url);
    pi_server_Url.path = '/Aircleaner_Control/';
    res.json(aa);
});

router.post('/speedup', (req, res, next) => {
    const aa = {};
    console.log('aircleaner speedup');
    pi_server_Url.path += "speedup";
    http.request(pi_server_Url).end();
    console.log(pi_server_Url);
    pi_server_Url.path = '/Aircleaner_Control/';
    res.json(aa);
});

router.post('/speeddown', (req, res, next) => {
    const aa = {};
    console.log('aircleaner speeddown');
    pi_server_Url.path += "speeddown";
    http.request(pi_server_Url).end();
    console.log(pi_server_Url);
    pi_server_Url.path = '/Aircleaner_Control/';
    res.json(aa);
});

module.exports = router;
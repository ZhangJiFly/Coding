  var express = require('express'),
  app = express(),
  server = require('http').createServer(app),
  io = require('socket.io').listen(server),
  mysql = require('mysql'),
  pass = require('pwd');

var update = function(user){
  //console.log(user);
  connection.query("UPDATE Student\n SET Salt='" + user.Salt + "', Password = '" + user.Password + "'\n WHERE Matric='" + user.Matric + "';", function(error, rows, file){
    if (error) throw error;
  });
}

var hash = function(user){
  pass.hash(user.Password, function(err, salt, hash){
    if (err) throw err;
    // store the salt & hash in the "db"
    user.Salt = salt;
    user.Password = JSON.stringify(hash);
    //console.log(user);
    update(user);
  })
}

var users = {};

app.use(express.bodyParser());
app.use(express.cookieParser('shhhh, very secret'));
app.use(express.session());
app.use(function(req, res, next){
  var err = req.session.error
    , msg = req.session.success;
  delete req.session.error;
  delete req.session.success;
  res.locals.message = '';
  if (err) res.locals.message = '<p class="msg error">' + err + '</p>';
  if (msg) res.locals.message = '<p class="msg success">' + msg + '</p>';
  next();
});
  
var connection = mysql.createConnection({
    host     : '127.0.0.1',
    user     : 'root',
    password : '',
    database : 'mydb'
});

// connection.query("SELECT * FROM STUDENT;", function(error, rows, file){
//   for (row in rows){
//     user = rows[row]
//     updateUsername(user);
//   }
// });

app.get('/restricted/:file', restrict, function(req, res){
  var file = req.params.file;
  res.sendfile("/Users/Crippled.Josh/Coding/Dissertation/code/restricted/" + file);
});

app.get('/logout', function(req, res){
  // destroy the user's session to log them out
  req.session.destroy(function(){
    res.redirect('/index.html');
  });
});

app.get('/:file',  function (req, res) {
  var file = req.params.file;
  res.sendfile("/Users/Crippled.Josh/Coding/Dissertation/code/" + file);

});

app.get('/js/libs/:lib/:file', function (req, res) {
  var file = req.params.file,
  lib = req.params.lib;
 res.sendfile("/Users/Crippled.Josh/Coding/Dissertation/code/js/libs/" + lib + '/' + file);
});

app.get('/:folder/:file', function (req, res) {
  var file = req.params.file,
    folder = req.params.folder;
    res.sendfile("/Users/Crippled.Josh/Coding/Dissertation/code/" + folder + '/' + file);
});

function authenticate(name, password, fn) {
  if (!module.parent) console.log('authenticating %s:%s', name, password);
  //look up prepared statements to sanetize statements. 
  connection.query("SELECT * FROM Student\n WHERE Username='" + name + "';", function(error, rows, file){
    var user = rows[0];
    // query the db for the given username
    if (!user) return fn(new Error('cannot find user'));
    // apply the same algorithm to the POSTed password, applying
    // the hash against the pass / salt, if there is a match we
    // found the user
    pass.hash(password, user.Salt, function(err, hash){
      if (err) return fn(err);
      if (JSON.stringify(hash) == user.Password) return fn(null, user);
      fn(new Error('invalid password'));
    });
  });
}

function restrict(req, res, next) {
  if (req.session.user) {
    next();
  } else {
    req.session.error = 'Access denied!';
    res.redirect('/login.html');
  }
}

function loggedin(req, res, next){
  if (req.session.user){
    res.redirect('/restricted/details.html');
  }
  else{
    next();
  }
}

app.get('/login', function(req, res){
  res.render('login.html');
});

app.post('/login', function(req, res){

  authenticate(req.body.username, req.body.password, function(err, user){
    if (user) {
      // Regenerate session when signing in
      // to prevent fixation 
      req.session.regenerate(function(){
        // Store the user's primary key 
        // in the session store to be retrieved,
        // or in this case the entire user object
        console.log(res);
        //users[] = user;
        req.session.user = user;
        req.session.success = 'Authenticated as ' + user.name
          + ' click to <a href="/logout">logout</a>. '
          + ' You may now access <a href="/restricted">/restricted</a>.';
        res.redirect('/restricted/details.html');
      });
    } else {
      req.session.error = 'Authentication failed, please check your username and password.';
      res.redirect('/index.html');
    }
  });
});

io.sockets.on('connection', function (socket) {
  // socket.emit('news', { user: "news" });
  // socket.on('details', function (data) {
  //   socket.emit('user', userX );
  // });
});

server.listen(8080);
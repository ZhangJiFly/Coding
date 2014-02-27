var express = require('express'),
app = express(),
server = require('http').createServer(app),
io = require('socket.io').listen(server),
mysql = require('mysql'),
jade = require('jade'),

pass = require('pwd');

var connection = mysql.createConnection({
    host     : '127.0.0.1',
    user     : 'root',
    password : '',
    database : 'mydb'
});

var auth = require('Authentication')(connection),
RStudents = require('StudentResponse')(connection),
RStaff = require('StaffResponse')(connection),
routes = require('routes')(app, auth, RStudents, RStaff),
query = require('QueryFunctions')(connection);

app.set('view engine', 'jade');
var createYear = function(num){
  return "<div class='row'><div class='panel panel-primary'><div class='panel-heading'>"+ num + "Year Course List</div><div class='panel-body'><div class='w2ui-label'> List:</div><div class='w2ui-field'><input type='list' style='width: 200px; box-sizing: border-box; padding-right: 14px;' placeholder=' class='w2field'/><div style='color: rgb(0, 0, 0); font-size: 14px; padding: 3px; margin-top: 1px; margin-bottom: 1px; margin-left: -16px'; class='w2ui-field-helper'></div><span class='legend'></span><div style='height: 30px;'></div></div></div></div></div>";
}
years = 3;
console.log("gay")
var createYears = function(){
  for(var i= 0; i<years;i++){
    var string = createYear(i);
    $('#years').append(string);
  }
}

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

query.updateStart(pass);

jadeTemp = {'details':jade.compile("/Users/Crippled.Josh/Coding/Dissertation/code/Student/details.jade"),
'courses':jade.compile("/Users/Crippled.Josh/Coding/Dissertation/code/Student/courses.jade"),
'advisor':jade.compile("/Users/Crippled.Josh/Coding/Dissertation/code/Staff/advisor.jade"),
'StaffHome':jade.compile("/Users/Crippled.Josh/Coding/Dissertation/code/Staff/home.jade"),
'school':jade.compile("/Users/Crippled.Josh/Coding/Dissertation/code/Staff/school.jade"),
'degree':jade.compile("/Users/Crippled.Josh/Coding/Dissertation/code/Staff/degree.jade")
};



app.post('/loginStudent', function(req, res){

  auth.authenticate(req.body.username, req.body.password, "Student", function(err, user){
    if (user) {
      req.session.regenerate(function(){
        req.session.user = user;
        req.session.level = 0;
        var StaffId = user.StaffId;
        connection.query("SELECT * FROM Staff WHERE StaffId= ?", StaffId, function(error, rows, file){
          var Advisor = rows[0]
          req.session.user.Advisor = Advisor;
          req.session.success = 'Authenticated as ' + user.name
            + ' click to <a href="/logout">logout</a>. '
           + ' You may now access <a href="/Student">/Student</a>.';
          res.redirect('/Student/home.html');
        });
      });
    } else {
      req.session.error = 'Authentication failed, please check your username and password.';
      res.redirect('/login.html');
    }
  });
});

app.post('/loginStaff', function(req, res){

  auth.authenticate(req.body.username, req.body.password, "Staff", function(err, user){
    if (user) {
      req.session.regenerate(function(){
        req.session.user = user;
        req.session.level = 1;
          req.session.success = 'Authenticated as ' + user.name
            + ' click to <a href="/logout">logout</a>. '
            + ' You may now access <a href="/Student">/Student</a>.';
          res.redirect('/Staff/home');
      });
    } else {
      req.session.error = 'Authentication failed, please check your username and password.';
      res.redirect('/login.html');
    }
  });
});


io.sockets.on('connection', function (socket) {
  socket.on('coursesPlease', function (data) {
    console.log(socket);
    query.getSchoolCourses(data, function(courses){
      socket.emit('courses', courses);
    }); 
  });
  socket.on('courseList', function (data) {
    query.updateCourseList(data);
    query.updateGroup(data);
  });
});


server.listen(8080);
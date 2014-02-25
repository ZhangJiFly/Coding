var express = require('express'),
app = express(),
server = require('http').createServer(app),
io = require('socket.io').listen(server),
mysql = require('mysql'),
jade = require('jade'),
pass = require('pwd');

app.set('view engine', 'jade');

var updatePassword = function(user, type){
  if (type){
    var query = connection.query("UPDATE STAFF\n SET Salt='" + user.Salt + "', Password = '" + user.Password + "'\n WHERE StaffId='" + user.StaffId + "';", function(error, rows, file){
    if (error) throw error;
    });
  }
  else{
    var query = connection.query("UPDATE Student\n SET Salt='" + user.Salt + "', Password = '" + user.Password + "'\n WHERE Matric='" + user.Matric + "';", function(error, rows, file){
    if (error) throw error;
    });
  }
}

var hash = function(user, type){
  pass.hash("password", function(err, salt, hash){
    if (err) throw err;
        // store the salt & hash in the "db"
    user.Salt = salt;
    user.Password = JSON.stringify(hash);
    updatePassword(user, type);
  })
}

var updateStart = function(){
  connection.query("SELECT * FROM STUDENT;", function(error, rows, file){
    for (row in rows){
      userX = rows[row]
      hash(userX, 0); 
    }
  });
  connection.query("SELECT * FROM STAFF;", function(error, rows, file){
    for (row in rows){
      userY = rows[row]
      hash(userY, 1); 
    }
  });
}

var updateCourseList = function(data){
  var values = [];
  values.push(data.listName);
  values.push(data.school);
  values.push(data.level);
  var query = connection.query("INSERT INTO Courselist (CourseListId, School, Level) VALUES (?,?,?);",values, function(error, rows, file){
    if (error) throw error;
  });
}

var updateGroup = function(data){
  var groupValues = [];
  var groupCourseValues = []
  var groups = data.groups;
  for (var i=0; i<groups.length;i++){
    groupValues.push([groups[i].credits, data.listName, i])
    for (var j = 0; j<groups[i].courses.length;j++){
      groupCourseValues.push([i, data.listName, groups[i].courses[j].CourseId])
    }
  }

  var query = connection.query("INSERT INTO Groups (Credits, CourseListId, GroupId) VALUES (?);",groupValues, function(error, rows, file){
    if (error) throw error;
  });

  var query = connection.query("INSERT INTO GroupHasCourse (GroupId, CourseListId, CourseId) VALUES (?);",groupCourseValues, function(error, rows, file){
    if (error) throw error;
  }); 
}

var courses = function(matric, callback){
  query = connection.query("SELECT Course.CourseID, Course.Name, Course.Credit, StudentHasCourse.Grade, StudentHasCourse.Status FROM Course INNER JOIN StudentHasCourse ON Course.CourseId = StudentHasCourse.CourseId WHERE StudentHasCourse.StudentMatric = ?", matric, function(error, rows, file){
    callback(rows);
  });
}   

var advisees = function(StaffId, callback){
  query = connection.query("SELECT Student.Forename, Student.Matric, Student.Degree, Student.Year FROM Student WHERE Student.StaffId = ?", StaffId, function(error, rows, file){
    callback(rows);
  });
} 

var degrees = function(school, callback){
  query = connection.query("SELECT Degree.Name FROM Degree WHERE Degree.School = ?", school, function(error, rows, file){
    callback(rows);
  });
}  

var courseLists = function(school, callback){
  query = connection.query("SELECT * FROM CourseList WHERE School = ?", school, function(error, rows, file){
    if (error) throw error;
    callback(rows);
  });
}   

var degreeCourseLists = function(degree, callback){
  query = connection.query("SELECT * FROM DegreeHasCourseList WHERE Degree = ?", degree, function(error, rows, file){
     if (error) throw error;
    callback(rows);
  });
} 

var getSchoolCourses = function(school, callback){
  var query = connection.query("Select * FROM Course WHERE Course.School = ?;", school, function(error, rows, file){
    if (error) throw error;
    callback(rows);
    });
} 


function authenticate(name, password, type, fn) {
  if (!module.parent) console.log('authenticating %s:%s', name, password);
  //look up prepared statements to sanetize statements. 
  connection.query("SELECT * FROM " + type + "\n WHERE Username= ?", name, function(error, rows, file){
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

function restrictStaff(req, res, next) {
  if (req.session.user && req.session.level) {
    next();
  } 
  else if(!req.session.level){
    res.redirect('/NoAcess.html');
  }
  else {
    req.session.error = 'Access denied!';
    res.redirect('/login.html');
  }
}

function restrictStudent(req, res, next) {
  if (req.session.user && !req.session.level) {
    next();
  }
  else if(req.session.level){
    res.redirect('/NoAcess.html');
  }
  else {
    req.session.error = 'Access denied!';
    res.redirect('/login.html');
  }
}

function loggedin(req, res, next){
  if (req.session.user){
    res.redirect('/Student/home.html');
  }
  else{
    next();
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
  
var connection = mysql.createConnection({
    host     : '127.0.0.1',
    user     : 'root',
    password : '',
    database : 'mydb'
});

updateStart();

jadeTemp = {'details':jade.compile("/Users/Crippled.Josh/Coding/Dissertation/code/Student/details.jade"),
'courses':jade.compile("/Users/Crippled.Josh/Coding/Dissertation/code/Student/courses.jade"),
'advisor':jade.compile("/Users/Crippled.Josh/Coding/Dissertation/code/Staff/advisor.jade"),
'StaffHome':jade.compile("/Users/Crippled.Josh/Coding/Dissertation/code/Staff/home.jade"),
'school':jade.compile("/Users/Crippled.Josh/Coding/Dissertation/code/Staff/school.jade"),
'degree':jade.compile("/Users/Crippled.Josh/Coding/Dissertation/code/Staff/degree.jade")
};

app.get('/Student/:file', restrictStudent, function(req, res){
  var file = req.params.file;
  var matric = req.session.user.Matric;
  if (file == "details"){

    var html
    var name = req.session.user.Forename + " " + req.session.user.Surname;

    var email = req.session.user.Email;
    var advisorName = req.session.user.Advisor.Forename + " " + req.session.user.Advisor.Surname;
    var advisorEmail = req.session.user.Advisor.Email
    html = jadeTemp[file](user = {name: name, matric: matric, email: email, advisorName:advisorName, advisorEmail:advisorEmail});
    res.render(html);
  }
  else if (file == "courses"){
    courses(matric, function(rows){
      html = jadeTemp[file](aaData = JSON.stringify(rows));
      res.render(html);
    });
  }
  else{
    res.sendfile("/Users/Crippled.Josh/Coding/Dissertation/code/Student/" + file);
    
  }
});

app.get('/Staff/:file', restrictStaff, function(req, res){
  var file = req.params.file;
  var StaffId = req.session.user.StaffId;
  var school = req.session.user.School;
  var degree = req.query.degree;
  if (file == "home"){
    var name = req.session.user.Forename + " " + req.session.user.Surname;
    var email = req.session.user.Email;
    var staffId = req.session.user.StaffId;
    userX = {name: name, staffId: staffId, email: email}
    var html = jadeTemp['StaffHome'](userX);
    res.render(html);
  }
  else if (file == "advisor"){
    advisees(StaffId, function(rows){
      var Data = JSON.stringify(rows);
      html = jadeTemp[file](aaData = JSON.stringify(rows));
      res.render(html);
    });
  }
  else if (file == "degree"){

    degreeCourseLists(degree, function(rows){
      html = jadeTemp[file](Degree = degree, School = school);
      res.render(html);
    });
  }
  else if (file == "school"){
    degrees(school, function(degreeRows){
      courseLists(school,function(courseRows){
        html = jadeTemp[file](Degrees = JSON.stringify(degreeRows), CL = JSON.stringify(courseRows), School = school);
        res.render(html);
      });
    });
  }
  else{
    res.sendfile("/Users/Crippled.Josh/Coding/Dissertation/code/Staff/" + file);   
  }
});

app.get('/login', function(req, res){
  res.render('/login.html');
});

app.get('/', function(req, res){
  res.redirect('/login.html');
});

app.get('/logout', function(req, res){
  // destroy the user's session to log them out
  req.session.destroy(function(){
    res.redirect('/login.html');
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

app.get('/js/libs/:lib/media/js/:file', function (req, res) {
  var file = req.params.file,
  lib = req.params.lib,
  sub1 = req.params.sub1,
  sub2 = req.params.sub2;
 res.sendfile("/Users/Crippled.Josh/Coding/Dissertation/code/js/libs/" + lib + '/media/js/' + file);
});

app.get('/:folder/:file', function (req, res) {
  var file = req.params.file,
    folder = req.params.folder;
    res.sendfile("/Users/Crippled.Josh/Coding/Dissertation/code/" + folder + '/' + file);
});

app.post('/loginStudent', function(req, res){

  authenticate(req.body.username, req.body.password, "Student", function(err, user){
    if (user) {
      req.session.regenerate(function(){
        req.session.user = user;
        req.session.level = 0;
        var StaffId = user.StaffId;
        query = connection.query("SELECT * FROM Staff WHERE StaffId= ?", StaffId, function(error, rows, file){
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

  authenticate(req.body.username, req.body.password, "Staff", function(err, user){
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
    getSchoolCourses(data, function(courses){
      socket.emit('courses', courses);
      // console.log(courses);
    }); 
  });
  socket.on('courseList', function (data) {
    // console.log("\n\n\n\n");
    // console.log(data);
    updateCourseList(data);
    updateGroup(data);
  });
});


server.listen(8080);
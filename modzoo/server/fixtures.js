if (Posts.find().count() === 0) {
  var now = new Date().getTime();


  var kyleId = Meteor.users.insert({
    profile: { name: 'kylevdm' }
  });
  var kyle = Meteor.users.findOne(kyleId);

  var personaId = Meteor.users.insert({
    profile: { name: 'drougnor' }
  });
  var persona = Meteor.users.findOne(personaId);

  var a = Posts.insert({
    title: 'Episode 23: Attack of the Case Clones',
    userId: kyle._id,
    author: kyle.profile.name,
    frontImage: '/resources/clones.jpg',
    content: 'Kyle starts the twenty-third episode of The Mod Zoo Podcast along with the normal rabble, Bill Owen from MNPCTech, Jeremy “EEL Ambiense” Birch, Cheapskate aka Munkey and Toby Kirkby! During this podcast we discuss the many clones that appeared at Computex from Thermaltake, as well as covering some listener questions and Mad Max Fury Road. SPOILER WARNING!',
    submitted: new Date(now - 1000),
    category: 'Podcast',
  });
  a1 = Posts.findOne(a);
  var b = Posts.insert({
    title: 'Rosewill R-Studio Sonas',
    userId: persona._id,
    author: persona.profile.name,
    frontImage: '/resources/test-review-pic.jpg',
    content: 'Headphones are an interesting topic when it comes to reviews, at least from a modding site POV. Without the right equipment, it’s hard to offer more than simple opinion, and everyone’s experience depends on their own situation. I had to take that all into account when I was told that Rosewill was sending out a pair to be reviewed. Initially, I tried to figure out how I would tackle them from a modding point of view, but realistically, you can only talk about how they look and what you might alter. Not very exciting from a modding perspective. So, I spent a couple of weeks familiarizing myself with their sound quality, their build quality and, of course, their looks. I digested it all and am now putting it all together for you here. First, let’s start with the reported stats from Rosewill',
    submitted: new Date(now - 100),
    category: 'Reviews',
    previousPost: {id: a1._id, title: a1.title},
  });
  b1 = Posts.findOne(b);
  var c = Posts.insert({
    title: 'Episode 25: Attack of the Case Clones',
    userId: kyle._id,
    author: kyle.profile.name,
    frontImage: '/resources/clones.jpg',
    content: 'Kyle starts the twenty-third episode of The Mod Zoo Podcast along with the normal rabble, Bill Owen from MNPCTech, Jeremy “EEL Ambiense” Birch, Cheapskate aka Munkey and Toby Kirkby! During this podcast we discuss the many clones that appeared at Computex from Thermaltake, as well as covering some listener questions and Mad Max Fury Road. SPOILER WARNING!',
    submitted: new Date(now - 10),
    category: 'Podcast',
    previousPost: {id: b1._id, title: b1.title},
  });
  c1 = Posts.findOne(c);
  var d = Posts.insert({
    title: 'Episode 26: Attack of the Case Clones',
    userId: kyle._id,
    author: kyle.profile.name,
    frontImage: '/resources/clones.jpg',
    content: 'Kyle starts the twenty-third episode of The Mod Zoo Podcast along with the normal rabble, Bill Owen from MNPCTech, Jeremy “EEL Ambiense” Birch, Cheapskate aka Munkey and Toby Kirkby! During this podcast we discuss the many clones that appeared at Computex from Thermaltake, as well as covering some listener questions and Mad Max Fury Road. SPOILER WARNING!',
    submitted: new Date(now - 1),
    category: 'Podcast',
    previousPost: {id: c1._id, title: c1.title},
  });
  d1 = Posts.findOne(d);
  console.log(d1);
  var e = Posts.insert({
    title: 'Episode 27: Attack of the Case Clones',
    userId: kyle._id,
    author: kyle.profile.name,
    frontImage: '/resources/clones.jpg',
    content: 'Kyle starts the twenty-third episode of The Mod Zoo Podcast along with the normal rabble, Bill Owen from MNPCTech, Jeremy “EEL Ambiense” Birch, Cheapskate aka Munkey and Toby Kirkby! During this podcast we discuss the many clones that appeared at Computex from Thermaltake, as well as covering some listener questions and Mad Max Fury Road. SPOILER WARNING!',
    submitted: new Date(now),
    category: 'Podcast',
    previousPost: {id: d1._id, title: d1.title},
  });
  e1 = Posts.findOne(e);

  Posts.update(a, {
    $set: {nextPost: {id: b1._id, title: b1.title}}
  });
  Posts.update(b, {
    $set: {nextPost: {id: c1._id, title: c1.title}}
  });
  Posts.update(c, {
    $set: {nextPost: {id: d1._id, title: d1.title}}
  });
  Posts.update(d, {
    $set: {nextPost: {id: e1._id, title: e1.title}}
  });
}
var express = require('express');
var router = express.Router();
var axios = require('axios');
const session = require('express-session');
const passport = require("passport");
// const cookieSession = require("cookie-session");
require("./passport-setup");

router.get('/logout', function (req, res) {
    req.logout();
    req.session.regenerate(function(err) {
        if (err) {
            console.log('Error regenerating session')
        } else {
            console.log('Session successfully regenerated')
        }
    })
    res.redirect('/');
});

router.get('/ping', function (req, res) {
    res.status(200).send("pong!");
});

// router.use(
//     cookieSession({
//         name: "area-session",
//         keys: ["key1, key2"],
//     })
// );

const isLoggedIn = (req, res, next) => {
    if (req.user) {
        req.session.email = req.user.emails[0].value;
        req.session.firstname = req.user.displayName;
        req.session.save(function(err) {
            if (err) {
                console.log("Error saving the session");
                return res.redirect('/ActionREAction');
            } else {
                console.log("Session successfully saved");
                next()
                return res.redirect('/ActionREAction');
            }
        })
    } else {
        res.sendStatus(401);
    }
};

router.use(passport.initialize());
router.use(passport.session());


router.get("/google/callback", (req, res) => res.send("callback here:"));

router.get("/failed", (req, res) => res.send("You Failed to Log in!"));
router.get("/good", isLoggedIn, (req, res) => {
    
});
router.get("/google", passport.authenticate("google", { scope: ["profile", "email"] }));
router.get("/google/auth/callback",passport.authenticate("google", { failureRedirect: "/failed" }),function (req, res) {
    res.redirect("/good");
});

router.get("/logoutGoogle", (req, res) => {
  req.logout();
  req.session.regenerate(function(err) {
    if (err) {
        console.log('Error regenerating session')
    } else {
        console.log('Session successfully regenerated')
    }
})
  res.redirect("/");
});

router.get('/login', function (req, res) {
    res.render('login.twig', { user: req.session.firstname });
});

router.post('/login', function (req, res) {
    var config = {
        method: 'post',
        url: 'http://server:8080/db/loginUser',
        headers: {
            'Content-Type': 'application/json'
        },
        data:  `{\"email\": \"${req.body.email}\", \"password\": \"${req.body.password}\"}`
    };
    console.log(config.data);
    axios(config)
        .then(function (response) {
            console.log(response.data);
            if (response.data.success === true) {
                req.session.email = req.body.email;
                req.session.save(function(err) {
                    if (err) {
                        console.log("Error saving the session");
                    } else {
                        console.log("Session email successfully saved");
                    }
                    return res.redirect('/ActionREAction');
                })
            } else {
                return res.render('login.twig', { error: true });
            }
        })
        .catch(function (error) {
            console.log(error);
            return res.render('login.twig', { error: true });
        });
});

router.get('/register', function (req, res) {
    res.render('register.twig', { user: req.session.firstname });
});

router.post('/register', function (req, res) {
    var config = {
        method: 'post',
        url: 'http://server:8080/db/createUser',
        headers: {
            'Content-Type': 'application/json'
        },
        data: `{\"firstname\": \"${req.body.firstname}\", \"name\": \"${req.body.name}\", \"email\": \"${req.body.email}\", \"password\": \"${req.body.password}\"}`
    };

    axios(config)
        .then(function (response) {
            console.log(response.data);
            if (response.data.success === true) {
                req.session.email = req.body.email;
                req.session.firstname = req.body.firstname;
                return res.redirect('/ActionREAction');
            } else {
                return res.render("register.twig", {error: true});
            }
            console.log(response.data.success);
        })
        .catch(function (error) {
            console.log(error);
        });
});

router.get('/', function (req, res) {
    res.render('index.twig', { user: req.session.firstname });
});

router.get('/profil', function (req, res) {
    res.render('profil.twig', {
        user: req.session.firstname,
        email: req.session.email,
        name: req.session.name,
        creationdate: req.session.creationdate
    });
});

router.post('/profil', function (req, res) {
//todo
    res.render('profil.twig', {
        user: req.session.firstname,
        email: req.session.email,
        name: req.session.name,
        creationdate: req.session.creationdate
    });
});


function sendMailFromNewsSubject(req, res) {
    var email = req.body.p3newsmail;
    var subject = req.body.p3newssubject;
    var data = JSON.stringify({email: email});

    var config = {
        method: 'post',
        url: 'http://server:8080/news/sendMailFromNewsSubject/' + subject,
        headers: { 
            'Content-Type': 'application/json'
        },
        data : data
    };

    axios(config)
        .then(function (response) {
            console.log(JSON.stringify(response.data));
        })
        .catch(function (error) {
            console.log(error);
        });
}

function sendMailOnNewMail(req, res) {
    var email = req.body.p1imapemail;
    var config = {
        method: 'get',
        url: 'http://server:8080/mailer/connectListen?email=' + email,
        headers: { }
      };
      
      axios(config)
      .then(function (response) {
        console.log(JSON.stringify(response.data));
      })
      .catch(function (error) {
        console.log(error);
      });
}

function epitechSendMessageMail(req, res) {
    var data = JSON.stringify({actionParameter: req.body.p1epitech});

    var config = {
        method: 'post',
        url: 'http://server:8080/epitech/sendMessageMail',
        headers: { 
            'Content-Type': 'application/json'
        },
        data : data
    };

    axios(config)
    .then(function (response) {
        console.log(JSON.stringify(response.data));
    })
    .catch(function (error) {
        console.log(error);
    });
}

function epitechSendMailOnCreditChange(req, res) {
    var email = req.body.p2epitechmail;
    var mailepitech = req.body.p2epitechepimail;
    var data = JSON.stringify({"update":"30s","action":"MAIL_GPA_CHANGE","target":email, "query":[mailepitech]});

    var config = {
      method: 'post',
      url: 'http://server:8080/automate/create',
      headers: { 
        'Content-Type': 'application/json'
      },
      data : data
    };

    axios(config)
    .then(function (response) {
      console.log(JSON.stringify(response.data));
    })
    .catch(function (error) {
      console.log(error);
    });
    
}

function GetNewBinomeEpitech(req, res) {
    var data = JSON.stringify({update:req.body.p3epitechtime,action:"MAIL_NEW_BINOME",target:req.body.p3epitechmail,query:[req.body.p3epitechepimail]});

    var config = {
      method: 'post',
      url: 'http://server:8080/automate/create',
      headers: { 
        'Content-Type': 'application/json'
      },
      data : data
    };
    
    axios(config)
    .then(function (response) {
      console.log(JSON.stringify(response.data));
    })
    .catch(function (error) {
      console.log(error);
    });
}

function sendRandomNewsToImgur(req, res) {
    var data = JSON.stringify({"data": "imgur"});

    var config = {
        method: 'post',
        url: 'http://server:8080/news/sendRandomNewsToImgur',
        headers: { },
        data: data
      };
      
      axios(config)
      .then(function (response) {
        console.log(JSON.stringify(response.data));
      })
      .catch(function (error) {
        console.log(error);
      });
}

function SendMailFromNewsCategory(req, res) {
    var email = req.body.newscategorymail;
    console.log("category:", req.body.newscategory)
    var category = req.body.newscategory;
    var data = JSON.stringify({email: email});
    var config = {
        method: 'post',
        url: 'http://server:8080/news/sendMailFromNewsCategory/' + category,
        headers: { 
            'Content-Type': 'application/json'
        },
        data : data
    };

    axios(config)
        .then(function (response) {
            console.log(JSON.stringifoooy(response.data));
        })
        .catch(function (error) {
            console.log(error);
        });
}

function SendMailOnLastNews(req, res) {
    var data = JSON.stringify({update:req.body.lastnewsupdate, "action":"MAIL_LAST_NEW", target:req.body.lastnewsemail});

    var config = {
      method: 'post',
      url: 'http://server:8080/automate/create',
      headers: { 
        'Content-Type': 'application/json'
      },
      data : data
    };
    
    axios(config)
    .then(function (response) {
      console.log(JSON.stringify(response.data));
    })
    .catch(function (error) {
      console.log(error);
    });
}


function SendRappelFromDate(req, res) {
    var email = req.body.emailrappeldate;
    var date = req.body.rappeldateimap
    var re = /^(\d{4,})-(\d{2})-(\d{2})[T ](\d{2}):(\d{2})(?::(\d{2}(?:\.\d+)?))?$/
    var result = date.match(re);

    month = parseInt(result[2]) - 1;
    day = parseInt(result[3]);

    var data = JSON.stringify({"actions":"MAIL",actionParameter: email,"date":{"year": parseInt(result[1]),"month":month,"day":day, "hour":parseInt(result[4]),"mins":parseInt(result[5]),"sec":0}});
    var config = {
        method: 'post',
        url: 'http://server:8080/scheduler/scheduler',
        headers: { 
            'Content-Type': 'application/json'
        },
        data : data
    };

    axios(config)
        .then(function (response) {
            console.log(JSON.stringify(response.data));
        })
        .catch(function (error) {
            console.log(error);
        });

}

function getRandomInfoOnDate(req, res) {
    var email = req.body.emailrandominfo;
    var date = req.body.randominfodate;
    var re = /^(\d{4,})-(\d{2})-(\d{2})[T ](\d{2}):(\d{2})(?::(\d{2}(?:\.\d+)?))?$/
    var result = date.match(re);

    month = parseInt(result[2]) - 1;
    day = parseInt(result[3]);
    var data = JSON.stringify({"actions":"NEWS",actionParameter: email,"date":{"year": parseInt(result[1]),"month":month,"day":day, "hour":parseInt(result[4]),"mins":parseInt(result[5]),"sec":0}});

    var config = {
        method: 'post',
        url: 'http://server:8080/scheduler/scheduler',
        headers: { 
            'Content-Type': 'application/json'
        },
        data : data
    };

    axios(config)
        .then(function (response) {
            console.log(JSON.stringify(response.data));
        })
        .catch(function (error) {
            console.log(error);
        });
}

function SendMailMarketInfoOnDate(req, res) {
    var email = req.body.emailmarketinfo;
    var date = req.body.marketinfodate;
    var symbol = req.body.marketsymbol;
    var re = /^(\d{4,})-(\d{2})-(\d{2})[T ](\d{2}):(\d{2})(?::(\d{2}(?:\.\d+)?))?$/
    var result = date.match(re);

    month = parseInt(result[2]) - 1;
    day = parseInt(result[3]);
    var data = JSON.stringify({"actions":"MARKET",actionParameter: email, "symbol": symbol,"date":{"year": parseInt(result[1]),"month":month,"day":day, "hour":parseInt(result[4]),"mins":parseInt(result[5]),"sec":0}});

    var config = {
        method: 'post',
        url: 'http://server:8080/scheduler/scheduler',
        headers: { 
            'Content-Type': 'application/json'
        },
        data : data
    };

    axios(config)
        .then(function (response) {
            console.log(JSON.stringify(response.data));
        })
        .catch(function (error) {
            console.log(error);
        });
}

function sendMailMeteoInfoOnDate(req, res) {
    var email = req.body.emailmeteoinfo;
    var date = req.body.meteoinfodate;
    var city = req.body.meteoinfocity;
    var re = /^(\d{4,})-(\d{2})-(\d{2})[T ](\d{2}):(\d{2})(?::(\d{2}(?:\.\d+)?))?$/
    var result = date.match(re);

    month = parseInt(result[2]) - 1;
    day = parseInt(result[3]);
    var data = JSON.stringify({"actions":"METEO",actionParameter: email, "city": city,"date":{"year": parseInt(result[1]),"month":month,"day":day, "hour":parseInt(result[4]),"mins":parseInt(result[5]),"sec":0}});

    var config = {
        method: 'post',
        url: 'http://server:8080/scheduler/scheduler',
        headers: { 
            'Content-Type': 'application/json'
        },
        data : data
    };

    axios(config)
        .then(function (response) {
            console.log(JSON.stringify(response.data));
        })
        .catch(function (error) {
            console.log(error);
        });
}

function sendCurrentMeteoMail(req, res) {
    var email = req.body.emailcurrentmeteo;
    var city = req.body.currentmeteocity;
    var data = JSON.stringify({"actions":"MAIL","actionParameter": email,"query": city});

    var config = {
        method: 'post',
        url: 'http://server:8080/meteo/sendCurrentMeteoMail',
        headers: { 
            'Content-Type': 'application/json'
        },
        data : data
    };

    axios(config)
    .then(function (response) {
        console.log(JSON.stringify(response.data));
    })
    .catch(function (error) {
        console.log(error);
    });
}

function whenTempIsSup(req, res) {
    var email = req.body.tempsupemail;
    var city = req.body.tempsupcity;
    var temp = parseInt(req.body.tempsuptemperature);
    var data = JSON.stringify({"update": "30s","action":"MAIL_METEO","target": email,"query":[city, temp]});

    var config = {
        method: 'post',
        url: 'http://server:8080/automate/create',
        headers: { 
            'Content-Type': 'application/json'
        },
        data : data
    };

    axios(config)
    .then(function (response) {
        console.log(JSON.stringify(response.data));
    })
    .catch(function (error) {
        console.log(error);
    });
}

function sendMeteoToImgur(req, res) {
    var city = req.body.imgurmeteocity;
    var data = JSON.stringify({"query":city});

    var config = {
      method: 'post',
      url: 'http://server:8080/meteo/sendMeteoToImgur',
      headers: { 
        'Content-Type': 'application/json'
      },
      data : data
    };
    
    axios(config)
    .then(function (response) {
      console.log(JSON.stringify(response.data));
    })
    .catch(function (error) {
      console.log(error);
    });
}

function sendThumbnailToImgur(req, res) {
    var search = req.body.ytthumbnailsubject;
    var data = JSON.stringify({"query":search});

    var config = {
      method: 'post',
      url: 'http://server:8080/youtube/sendThumbnailToImgur',
      headers: { 
        'Content-Type': 'application/json'
      },
      data : data
    };
    
    axios(config)
    .then(function (response) {
      console.log(JSON.stringify(response.data));
    })
    .catch(function (error) {
      console.log(error);
    });
}

function sendMailOnNewVideoInChannel(req, res) {
    var email = req.body.newvidemail;
    var channelID = req.body.newvidchannel;
    var data = JSON.stringify({"update":"30s","action":"MAIL_VIDEO_YOUTUBE","target": email,"query":[channelID]});

    var config = {
      method: 'post',
      url: 'http://server:8080/automate/create',
      headers: { 
        'Content-Type': 'application/json'
      },
      data : data
    };
    axios(config)
    .then(function (response) {
      console.log(JSON.stringify(response.data));
    })
    .catch(function (error) {
      console.log(error);
    });
}

function sendMailForXViewsYoutubeChannel(req, res) {
    var email = req.body.xviewsemail;
    var channelID = req.body.xviewschannel;
    var view_number = parseInt(req.body.xviewsviews);
    var data = JSON.stringify({"update":"30s","action":"MAIL_NEW_VIEWS","target": email,"query":[channelID,view_number]});

    var config = {
      method: 'post',
      url: 'http://server:8080/automate/create',
      headers: { 
        'Content-Type': 'application/json'
      },
      data : data
    };
    
    axios(config)
    .then(function (response) {
      console.log(JSON.stringify(response.data));
    })
    .catch(function (error) {
      console.log(error);
    }); 
}

router.get('/ActionREAction', function (req, res) {
    if (req.session.email && !req.session.firstname) {
        var config = {
            method: 'get',
            url: `http://server:8080/db/getUser?search=${req.session.email}`,
            headers: { }
        };
        axios(config)
        .then(function (response) {
            req.session.firstname = response.data.firstname;
            req.session.name = response.data.name;
            req.session.creationdate = response.data.date_of_creation;
            req.session.save(function (err) {
                if (err) {
                    console.log("Error saving the session");
                } else {
                    console.log("Session firstname successfully saved");
                }
                res.render('ActionREAction.twig', { user: req.session.firstname });
            });
        })
        .catch(function (error) {
            console.log(error);
        });
    }
    else {
        res.render('ActionREAction.twig', { user: req.session.firstname });
    }
});

router.post('/ActionREAction', (req, res) => {
    if (req.body.p1epitech)
        epitechSendMessageMail(req, res); //check
    if (req.body.p2epitechmail)
        epitechSendMailOnCreditChange(req, res) //check
    if (req.body.p3epitechmail)
        GetNewBinomeEpitech(req, res); //check
    res.render('ActionREAction.twig', { user: req.session.firstname });
});

router.post('/news_section', (req, res) => {
    if (req.body.imgurnews)
        sendRandomNewsToImgur(req, res); //check
    if (req.body.newscategory)
        SendMailFromNewsCategory(req, res); //check
    if (req.body.lastnewsupdate)
        SendMailOnLastNews(req, res); //check
    if (req.body.p3newsmail)
        sendMailFromNewsSubject(req, res); //check
    res.render('news_section.twig', { user: req.session.firstname });
});

router.post('/meteo_section', (req, res) => {
    if (req.body.currentmeteocity)
        sendCurrentMeteoMail(req, res); //check
    if (req.body.tempsupemail)
        whenTempIsSup(req, res); //check
    if(req.body.imgurmeteocity)
        sendMeteoToImgur(req, res); //check
    res.render('meteo_section.twig', { user: req.session.firstname });
});

router.post('/scheduler_section', (req, res) => {
    if (req.body.emailmeteoinfo)
        sendMailMeteoInfoOnDate(req, res); //check
    if (req.body.rappeldateimap)
        SendRappelFromDate(req, res); //check
    if (req.body.emailrandominfo)
        getRandomInfoOnDate(req, res); //check
    if (req.body.emailmarketinfo)
        SendMailMarketInfoOnDate(req, res); //check
    res.render('scheduler_section.twig', { user: req.session.firstname });
});

router.post('/youtube_section', (req, res) => {
    if(req.body.ytthumbnailsubject)
        sendThumbnailToImgur(req, res); //check
    if (req.body.newvidchannel)
        sendMailOnNewVideoInChannel(req, res); //check
    if (req.body.xviewsemail)
        sendMailForXViewsYoutubeChannel(req, res); //check
    res.render('youtube_section.twig', { user: req.session.firstname });
});

router.post('/mailer_section', (req, res) => {
    if (req.body.p1imapemail)
        sendMailOnNewMail(req, res);
    res.render('mailer_section.twig', { user: req.session.firstname });
});

router.post('/API_settings', function (req, res, next) {

    var Plugin1infos = req.body.Plugin1infos;
    var Plugin2infos = req.body.Plugin2infos;

    if (Plugin1infos) {
        var config = {
            method: 'get',
            url: 'http://server:8080/epitech/login/' + Plugin1infos,
            headers: { },
          };
          axios(config)
          .then(function (response) {
            console.log(JSON.stringify(response.data));
          })
          .catch(function (error) {
            console.log(error);
          });
    }

    if (Plugin2infos) {
        var config = {
            method: 'post',
            url: 'http://server:8080/imgur/access_token_via_pin?pin=' + Plugin2infos,
            headers: { },
          };
          axios(config)
          .then(function (response) {
            console.log(JSON.stringify(response.data));
          })
          .catch(function (error) {
            console.log(error);
          });
    }
    res.render('API_settings.twig', { user: req.session.firstname });
});

router.post('/deleteAccount', function (req, res) {
    var data = JSON.stringify({email: req.session.email});

    var config = {
        method: 'delete',
        url: 'http://server:8080/db/deleteUser',
        headers: { 
            'Content-Type': 'application/json'
        },
        data : data
    };
    axios(config)
        .then(function (response) {
            console.log(JSON.stringify(response.data));
            req.session.regenerate(function(err) {
                if (err) {
                    console.log('Error regenerating session')
                } else {
                    console.log('Session successfully regenerated')
                }
            })
            res.redirect('/');
        })
        .catch(function (error) {
            res.render('profil.twig', { user: req.session.firstname, email: req.session.email });
            console.log(error);
        });

});

router.get('/API_settings', function (req, res) {
    res.render('API_settings.twig', { user: req.session.firstname });
});

router.get('/news_section', function (req, res) {
    res.render('news_section.twig', { user: req.session.firstname });
});

router.get('/meteo_section', function (req, res) {
    res.render('meteo_section.twig', { user: req.session.firstname });
});

router.get('/scheduler_section', function (req, res) {
    res.render('scheduler_section.twig', { user: req.session.firstname });
});

router.get('/youtube_section', function (req, res) {
    res.render('youtube_section.twig', { user: req.session.firstname });
});

router.get('/mailer_section', function (req, res) {
    res.render('mailer_section.twig', { user: req.session.firstname });
});

router.get('/client.apk', function (req, res) {
    res.render('client.apk.twig', { user: req.session.firstname });
});

module.exports = router;
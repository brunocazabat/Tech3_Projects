const passport = require("passport");
const GoogleStrategy = require("passport-google-oauth20").Strategy;

passport.serializeUser(function (user, done) {
  done(null, user);
});

passport.deserializeUser(function (user, done) {
  done(null, user);
});

passport.use(
  new GoogleStrategy(
    {
      clientID:
        "524667447554-g52kl8ts59u6o367c5nm73httevmbrn8.apps.googleusercontent.com",
      clientSecret: "fRdllhgXfys6pXYepCBrIOWn",
      callbackURL: "http://localhost:8081/google/auth/callback",
    },
    function (accessToken, refreshToken, profile, done) {
      console.log(profile.displayName, profile.emails);
      return done(null, profile);
    }
  )
);

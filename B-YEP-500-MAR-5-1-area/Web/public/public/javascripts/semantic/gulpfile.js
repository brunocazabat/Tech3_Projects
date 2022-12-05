
var
  gulp         = require('gulp-help')(require('gulp')),

  config       = require('./tasks/config/user'),

  watch        = require('./tasks/watch'),

  build        = require('./tasks/build'),
  buildJS      = require('./tasks/build/javascript'),
  buildCSS     = require('./tasks/build/css'),
  buildAssets  = require('./tasks/build/assets'),

  clean        = require('./tasks/clean'),
  version      = require('./tasks/version'),

  serveDocs    = require('./tasks/docs/serve'),
  buildDocs    = require('./tasks/docs/build'),

  buildRTL     = require('./tasks/rtl/build'),
  watchRTL     = require('./tasks/rtl/watch')
;

gulp.task('default', false, [
  'watch'
]);

gulp.task('watch', 'Watch for site/theme changes', watch);

gulp.task('build', 'Builds all files from source', build);
gulp.task('build-javascript', 'Builds all javascript from source', buildJS);
gulp.task('build-css', 'Builds all css from source', buildCSS);
gulp.task('build-assets', 'Copies all assets from source', buildAssets);

gulp.task('clean', 'Clean dist folder', clean);
gulp.task('version', 'Displays current version of Semantic', version);


gulp.task('serve-docs', 'Serve file changes to SUI Docs', serveDocs);
gulp.task('build-docs', 'Build all files and add to SUI Docs', buildDocs);


if(config.rtl) {
  gulp.task('watch-rtl', 'Watch files as RTL', watchRTL);
  gulp.task('build-rtl', 'Build all files as RTL', buildRTL);
}

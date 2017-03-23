const addon = require('bindings')('quiethours')

function getIsQuietHours() {
  if (process.platform !== 'win32') {
    throw new Error('windows-quiet-hours works only on Windows')
  }

  return addon.isQuietHours();
}

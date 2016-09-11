const addon = require('bindings')('quiethours')

module.exports = {
  getIsQuietHours: addon.isQuietHours
}

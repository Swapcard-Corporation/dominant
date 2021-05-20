const path = require('path');

const HtmlWebpackPlugin = require('html-webpack-plugin');

module.exports = {
  mode:'development',
  entry: {
    index: './demo/index.ts',
  },

  plugins: [
    new HtmlWebpackPlugin({
      title: 'Dominant'
    })
  ],
  output: {
    filename: '[name].bundle.js',
    path: path.resolve(__dirname, 'demo'),
    clean: true,
  }
};

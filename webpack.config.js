const path = require('path');
const { BundleAnalyzerPlugin } = require('webpack-bundle-analyzer');

module.exports = ({ bundle }) => {
  const entry = Object.assign(
    {
      simple: './lib/js/src/simple/simpleRoot.js',
    },
    bundle ? {} : { interop: './src/interop/interopRoot.js' },
  );

  return {
    entry,
    output: {
      path: path.join(__dirname, 'bundledOutputs'),
      filename: '[name].js',
    },
    plugins: bundle ? [new BundleAnalyzerPlugin()] : [],
  };
};

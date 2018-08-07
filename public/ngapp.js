// MODULE
var app = angular.module('SubredditScraper', ['ngMaterial', 'ngMessages']);

app.config(function($mdThemingProvider) {
    $mdThemingProvider.theme('default')
        .primaryPalette('pink')
        .accentPalette('orange');
});

// HOME CONTROLLER
app.controller('homeController', ['$scope', '$http', function($scope, $http) {
    $scope.myItems = [];
    $scope.color = {
        red: 10
    };
    $scope.stat = 'scores';
    $scope.backend = 'rbtree';
    $scope.buttonClick = false;
    $scope.query = function(searchText) {
        return $http
            .get('/search')
            .then(function(data) {
                console.log(data);
                return data.data;
            })
            .catch(function(data, error) {
                console.log(error);
            });
    };
    $scope.submit = function submit() {
        var input = {};
        input.args = ['-n', $scope.color.red, '-s', $scope.stat, '-b', $scope.backend];
        input.subreddits = $scope.myItems;
        $http.post('/reddit', input)
            .then(function (data) {
                $scope.stats = [];
                for (var key in data.data) {
                    data.data[key].Name = key;
                    $scope.stats.push(data.data[key]);
                }
            })
            .catch(function(data, error) {
                console.log(error);
            });
        $scope.buttonClick = true;
    };
}]);

﻿// Copyright (c) Converter Systems LLC. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

using Workstation.ServiceModel.Ua;

namespace RobotHmi.ViewModels
{
    /// <summary>
    /// A view model for Axis1.
    /// </summary>
    [Subscription("opc.tcp://localhost:55000", publishingInterval: 500, keepAliveCount: 20)]
    public class Axis1ViewModel : SubscriptionBase, IAxisViewModel
    {
        /// <summary>
        /// Gets the value of Axis.
        /// </summary>
        [MonitoredItem(nodeId: "ns=2;i=8")]
        public float Axis
        {
            get { return this.axis; }
            private set { this.SetProperty(ref this.axis, value); }
        }

        private float axis;

        /// <summary>
        /// Gets the DisplayName.
        /// </summary>
        public string DisplayName => "Axis 1";
    }
}
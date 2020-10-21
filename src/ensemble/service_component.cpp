/*
 * Copyright (C) 2017 Opendigitalradio (http://www.opendigitalradio.org/)
 * Copyright (C) 2017 Felix Morgner <felix.morgner@hsr.ch>
 * Copyright (C) 2017 Tobias Stauber <tobias.stauber@hsr.ch>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 *    may be used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "dab/ensemble/service_component.h"
#include "dab/ensemble/subchannel.h"

namespace dab
  {
  std::uint16_t service_component::id() const
    {
    return m_id;
    }

  transport_mechanism service_component::transport() const
    {
    return m_transport;
    }

  bool service_component::primary() const
    {
    return m_isPrimary;
    }

  bool service_component::ca_applies() const
    {
    return m_caApplies;
    }

  std::shared_ptr<internal::subchannel> service_component::subchannel() const
    {
    return m_subchannel;
    }

  std::uint8_t service_component::type() const
    {
    return m_type;
    }

  std::shared_ptr<service_component> service_component::make(std::uint16_t const id, transport_mechanism const transport,
                                                             bool const isPrimary, bool const caApplies)
    {
    return std::shared_ptr<service_component>(new service_component{id, transport, isPrimary, caApplies});
    }

  service_component::service_component(std::uint16_t const id, transport_mechanism const transport,
                                       bool const isPrimary, bool const caApplies)
    : m_id{id},
      m_transport{transport},
      m_isPrimary{isPrimary},
      m_caApplies{caApplies}
    {
    if(transport == transport_mechanism::stream_audio || transport == transport_mechanism::package_data)
      {
      m_subchannelId = id & 63;
      m_type = (id >> 6) & 63;
      }
    }

  void service_component::subchannel(std::shared_ptr<internal::subchannel> subchannel)
    {
    if(subchannel)
      {
      m_subchannel = subchannel;
      m_subchannelId = subchannel->id();
      }
    }

  void service_component::type(std::uint8_t const type)
    {
    m_type = type;
    }

  }
